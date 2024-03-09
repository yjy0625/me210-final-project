#include "line_sensor.h"
#include "proximity_sensor.h"
//#include "gyro.h"
#include "base_motor.h"
#include "Metro.h"

#define USE_TIMER_1 true
#define USE_TIMER_2 true

#include "TimerInterrupt.h"
//#include "ISR_Timer.h"
#include <Keyboard.h>
#include <Arduino.h>   
#include <QTRSensors.h>

#define LINE_TRACKER_1_TIME 10000
#define FORWARD_0_TIME 500
#define FORWARD_1_TIME 300
#define FORWARD_2_TIME 1000
#define SHOOT_TIME 5000


#define BALL_MOTOR_CONTROL_PIN A1
#define ON_PIN A3

#define READY_STATE -1
#define CALIBRATION_STATE 0
#define LINE_TRACKING_1 1
#define FORWARD_1 2
#define LINE_TRACKING_2 3
#define GOING_ALONG_WALL 4
#define GO_SHOOTING 5
#define FINAL_SHOOT 6
#define CELEBRATE_STATE 7



#define BLACK_LINE_THRES 600

int state = 0;

bool DEBUG_MODE = false;

float distance1=-1, distance2=-1, distance3=-1, distance;
bool calibrated1 = false, calibrated2 = false;
// bool calibrated1 = true, calibrated2 = true;
bool lineTrackerEnabled = false;

static Metro lineTracker1Timer = Metro(LINE_TRACKER_1_TIME);
static Metro forward0Timer = Metro(FORWARD_0_TIME);
static Metro forward1Timer = Metro(FORWARD_1_TIME);
static Metro forward2Timer = Metro(FORWARD_2_TIME);
static Metro shootTimer = Metro(SHOOT_TIME);


//Gyro gyro(ITimer1);
BaseMotor baseMotor;
LineSensor lineSensor;
ProximitySensor proxSensor;


void setup() {
  if(Serial) {
    Serial.begin(9600);
    Serial.println("Start");
  }

  delay(1000);
  pinMode(BALL_MOTOR_CONTROL_PIN, OUTPUT);
  stopBallMotor();

  pinMode(A2, OUTPUT);
  digitalWrite(A2, 0);
  checkSwitch();

  baseMotor = BaseMotor();
  proxSensor.init(ITimer1);
  // Serial.println("Prox sensor initialized");
  lineSensor.init();

  baseMotor.stopAll();

  ITimer2.init();
  ITimer2.setFrequency(lineSensor.controllerConfig.freq, lineTrackerTimerHandler);

  //Serial.println("Initialized");
  delay(5000);
}

void lineTrackerTimerHandler(){
  if (!lineTrackerEnabled) return;

  lineSensor.lineTrackerHandler();
  baseMotor.setVoltages(lineSensor.controllerConfig.ul, lineSensor.controllerConfig.ur);
}

void checkSwitch() {
  // set which side we are on based on switch
  pinMode(A5, INPUT);
  pinMode(A4, OUTPUT);
  if(analogRead(A5) > 500) {
    if(Serial) {
      Serial.println("switch high");
    }
    // turn clockwise => switch; counterclockwise => do not switch
    baseMotor.switchLeftRight();
    lineSensor.flip = true;
    digitalWrite(A4, 1); // send high and low value
    digitalWrite(A2, 1); // send value available
  }
  else {
    if(Serial) {
      Serial.println("switch low");
    }
    digitalWrite(A4, 0);
    digitalWrite(A2, 1);
  }
}

void loop() {
  lineSensor.readValues();

  proxSensor.read();
  distance = recordDistance(proxSensor.distance * 7.5);

  // // Serial.print("Proximity: ");
  // // Serial.println(distance);

  // // Serial.print("Line1: ");
  // // Serial.print(lineSensor.sensor_l);
  // // Serial.print(" Line2: ");
  // // Serial.print(lineSensor.sensor_m);
  // // Serial.print(" Line3: ");
  // // Serial.println(lineSensor.sensor_r);

  if (!DEBUG_MODE){

    //State Machine

    // Start State
    if (state == READY_STATE) {
      if (!Serial.available()) {
        return;
      }
      String inputString = Serial.readStringUntil('\n');

      if (inputString.equals("w")) {
        // Serial.println("Start playing.");
        state = CALIBRATION_STATE;
      } 

    }

    // 0
    if (state == CALIBRATION_STATE){
      if(Serial) {
        Serial.print("Proximity: ");
        Serial.println(distance);
      }
      if (!calibrated1){
        if (!calibrated1 && (distance > 30.0)) {
          baseMotor.turnRightPrimitive();
        } else {
          baseMotor.stopAll(); 
          calibrated1 = true;
        }
      } else {
        if (!calibrated2 && (distance > 100.0 || distance < 86.0)) {
          baseMotor.turnLeftPrimitive();
        } else {
          baseMotor.stopAll(); 
          calibrated2 = true;
        }
      }
      if (calibrated1 && calibrated2) {
        transition_to_LINE_TRACKING_1();
      }
    } 
      
    // 1
    else if (state == LINE_TRACKING_1){
      // check code for transition and lineTrackerTimerHandler
      if (lineTracker1Timer.check()) {
        transition_to_FORWARD_1();
      }
    }

    // 2
    else if (state == FORWARD_1){
      // finally see a horizontal black line after going straight for a while
      if (forward1Timer.check() && lineSensor.getMax() > BLACK_LINE_THRES) {
        transition_to_LINE_TRACKING_2();
      }
    }

    // 3
    else if (state == LINE_TRACKING_2){
      // track until we are close to the wall
      if (distance < 9.0) {
        transition_to_GOING_ALONG_WALL();
      }
    }

    // 4
    else if (state == GOING_ALONG_WALL){
      if (forward2Timer.check() && distance < 8.0) {
        transition_to_GO_SHOOTING();
      }

    }

    // 5
    else if (state == GO_SHOOTING){
      if (distance < 5.0) {
        transition_to_FINAL_SHOOT();
      }
    }

    // 6
    else if (state == FINAL_SHOOT){
      if (shootTimer.check()){
        stopBallMotor();
        transition_to_CELEBRATE_STATE();
      }
    }


  } else {
    if (!Serial.available()) {
      return;
    }
    // // Serial.println(gyro.readAngX());
    // delay(1000);

    String inputString = Serial.readStringUntil('\n');
    // Serial.println("Pressed");
    if (inputString.equals("w")) {
      baseMotor.moveForward(12);
    } else if (inputString.equals("s")) {
      baseMotor.moveBackward(12);
    } else if (inputString.equals("a")) {
      baseMotor.turnLeftPrimitive();
    } else if (inputString.equals("d")) {
      baseMotor.turnRightPrimitive();
    } else if (inputString.equals("q")) {
      startBallMotor();
    } else if (inputString.equals("e")) {
      stopBallMotor();
    } else {
      baseMotor.stopAll();
      stopBallMotor();
    }
  }
}

void transition_to_LINE_TRACKING_1(){
  state = LINE_TRACKING_1;
  // Serial.println("Direction calibrated. Start tracking 1.");
  baseMotor.moveForward(12);
  delay(FORWARD_0_TIME);
  baseMotor.stopAll();
  lineTrackerEnabled = true;
  lineTracker1Timer.reset();
}

void transition_to_FORWARD_1(){
  state = FORWARD_1;
  lineTrackerEnabled = false;
  // Serial.println("Finished line tracking 1, now going forward.");
  forward1Timer.reset();
  baseMotor.moveForward(10);
}

void transition_to_LINE_TRACKING_2(){
  state = LINE_TRACKING_2;
  // Serial.println("Met a black line while going forward, turning to it.");
  baseMotor.turnLeftFixedBlock();
  // Serial.println("Start tracking 2.");
  lineTrackerEnabled = true;
}

void transition_to_GOING_ALONG_WALL() {
  state = GOING_ALONG_WALL;
  lineTrackerEnabled = false;
  // Serial.println("Seeing the wall. Turning right");
  baseMotor.turnRightFixedBlockAgainstContactZone();
  // Serial.println("Ready to go along the wall");
  forward2Timer.reset();
  baseMotor.moveForward(12);
}

void transition_to_GO_SHOOTING(){
  state = GO_SHOOTING;
  // Serial.println("End of wall, turning left");
  baseMotor.turnLeftFixedBlockShootingZone();
  // Serial.println("Ready for final approach");
  baseMotor.moveForward(12);
}

void transition_to_FINAL_SHOOT(){
  baseMotor.setVoltages(12, 11);
  delay(500);
  baseMotor.setVoltages(-12, -12);
  delay(1000);
  baseMotor.setVoltages(7, -7);
  delay(500);
  baseMotor.setVoltages(12, 12);
  delay(1000);

  baseMotor.stopAll();
  state = FINAL_SHOOT;
  // Serial.println("SHOOT!!!!!");
  startBallMotor();
  shootTimer.reset();
}

void transition_to_CELEBRATE_STATE(){
  state = -1;
  // Serial.println("CELEBRATE");
  baseMotor.stopAll();
  delay(500);
  startBallMotor();
  delay(1000);
  stopBallMotor();
  calibrated1 = false;
  calibrated2 = false;
}

float recordDistance(float d){
  distance1 = distance2;
  distance2 = distance3;
  distance3 = d;
  
  if (distance2 == -1 || distance1 == -1) {
    return distance3;
  }

  return min(max(distance1, distance2), min(max(distance1, distance3), max(distance2, distance3)));

}

void stopBallMotor(){
  analogWrite(BALL_MOTOR_CONTROL_PIN, 0);
}

void startBallMotor(){
  analogWrite(BALL_MOTOR_CONTROL_PIN, 1000);
}