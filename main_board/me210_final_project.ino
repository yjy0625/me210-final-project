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

void setup() {
  Serial.begin(9600);
  Serial.print("Start");
  delay(1000);
  baseMotor = BaseMotor();
  proxSensor.init(ITimer1);
  Serial.println("Prox sensor initialized");
  lineSensor.init();

  baseMotor.stopAll();

  //ITimer2.init();
  //ITimer2.setFrequency(lineSensor.controllerConfig.freq, lineTrackerTimerHandler);
  Serial.println("Initialized");

  pinMode(BALL_MOTOR_CONTROL_PIN, OUTPUT);
  stopBallMotor();
}

void lineTrackerTimerHandler(){
  lineSensor.lineTrackerHandler();
  baseMotor.setVoltages(lineSensor.controllerConfig.ul, lineSensor.controllerConfig.ur);
}

void loop() {
  lineSensor.readValues();

  Serial.print("Proximity: ");
  Serial.println(proxSensor.read());
  
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
    baseMotor.turnLeft(12);
  } else if (inputString.equals("d")) {
    baseMotor.turnRight(12);
  } else if (inputString.equals("q")) {
    startBallMotor();
  } else if (inputString.equals("e")) {
    stopBallMotor();
  } else {
    baseMotor.stopAll();
    stopBallMotor();
  }

}

void stopBallMotor(){
  analogWrite(BALL_MOTOR_CONTROL_PIN, 0);
}

void startBallMotor(){
  analogWrite(BALL_MOTOR_CONTROL_PIN, 1000);
}