#include "line_sensor.h"
#include "proximity_sensor.h"
//#include "gyro.h"
#include "base_motor.h"

#define USE_TIMER_1 true
#define USE_TIMER_2 true

#include "TimerInterrupt.h"
//#include "ISR_Timer.h"
#include <Keyboard.h>
#include <Arduino.h>
#include <QTRSensors.h>

//Gyro gyro(ITimer1);
BaseMotor baseMotor;
LineSensor lineSensor;
ProximitySensor proxSensor;

#define BALL_MOTOR_CONTROL_PIN A1

#define CALIBRATION_STATE 0
#define LINE_TRACKING_1 1

int state = -1;

bool DEBUG_MODE = true;

float distance1=-1, distance2=-1, distance3=-1, distance;
// bool calibrated1 = false, calibrated2 = false;
bool calibrated1 = true, calibrated2 = true;


void setup() {
  Serial.begin(9600);
  Serial.println("Start");
  delay(1000);
  baseMotor = BaseMotor();
  proxSensor.init(ITimer1);
  Serial.println("Prox sensor initialized");
  lineSensor.init();

  baseMotor.stopAll();

  ITimer2.init();
  ITimer2.setFrequency(lineSensor.controllerConfig.freq, lineTrackerTimerHandler);
  Serial.println("Initialized");

  pinMode(BALL_MOTOR_CONTROL_PIN, OUTPUT);
  stopBallMotor();
}

void lineTrackerTimerHandler(){
  if (state != LINE_TRACKING_1) return;

  lineSensor.lineTrackerHandler();
  baseMotor.setVoltages(lineSensor.controllerConfig.ul, lineSensor.controllerConfig.ur);
}

void loop() {
  lineSensor.readValues();

  float d = proxSensor.read();
  distance = recordDistance(d);

  Serial.print("Proximity: ");
  Serial.print(d);
  Serial.print(" ");
  Serial.println(distance);


  if (!DEBUG_MODE){
    if (state == -1) {
      if (!Serial.available()) {
        return;
      }
      String inputString = Serial.readStringUntil('\n');

      if (inputString.equals("w")) {
        Serial.println("Start playing.");
        state = 0;
      } 

    }


    if (state == CALIBRATION_STATE){
      if (!calibrated1){
        if (!calibrated1 && (distance > 30.0)) {
          baseMotor.turnRightPrimitive();
        } else {
          baseMotor.stopAll(); 
          calibrated1 = true;
        }
      } else {
        if (!calibrated2 && (distance > 110.0 || distance < 70.0)) {
          baseMotor.turnLeftPrimitive();
        } else {
          baseMotor.stopAll(); 
          calibrated2 = true;
        }
      }
      if (calibrated1 && calibrated2) {
        state = LINE_TRACKING_1;
        Serial.println("Direction calibrated");
      }
    } else if (state == LINE_TRACKING_1){

    }

  } else {
    if (!Serial.available()) {
      return;
    }
    // Serial.println(gyro.readAngX());
    // delay(1000);

    String inputString = Serial.readStringUntil('\n');
    Serial.println("Pressed");
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