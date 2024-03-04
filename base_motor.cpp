#include "base_motor.h"

BaseMotor::BaseMotor(int leftEn, int leftIn1, int leftIn2, int rightEn, int rightIn1, int rightIn2) {
  le = leftEn;
  l1 = leftIn1;
  l2 = leftIn2;
  re = rightEn;
  r1 = rightIn1;
  r2 = rightIn2;

  pinMode(le, OUTPUT);
  pinMode(re, OUTPUT);
  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
}

void BaseMotor::moveForward(float v) {
  setLeftVoltage(v);
  setRightVoltage(v);
}

void BaseMotor::moveBackward(float v) {
  setLeftVoltage(-v);
  setRightVoltage(-v);
}

void BaseMotor::turnLeft(float v) {
  setLeftVoltage(v);
  setRightVoltage(-v);
}

void BaseMotor::turnRight(float v) {
  setLeftVoltage(-v);
  setRightVoltage(v);
}

void BaseMotor::stopAll() {
  setLeftVoltage(0);
  setRightVoltage(0);
}

void BaseMotor::setRightVoltage(float v) {
  v = v * MOTOR_SCALE;
  v = constrain(v, 0, 12); 
  int speed = map(abs(v), 0, 12, 0, 255);
  if (abs(v) < EPS){
    analogWrite(le, 0);
    return;
  }
  int dir;
  if (v > 0) {
    dir = 1;
  } else {
    dir = 0
  } 
  digitalWrite(r1, 1 ^ dir ^ MOTOR_RIGHT_DIR);
  digitalWrite(r2, 1 ^ dir ^ MOTOR_RIGHT_DIR);
  analogWrite(re, speed);
}

void BaseMotor::setLeftVoltage(float v) {
  v = v * MOTOR_SCALE;
  v = constrain(v, 0, 12); 
  int speed = map(abs(v), 0, 12, 0, 255);
  if (abs(v) < EPS){
    analogWrite(re, 0);
    return;
  }
  int dir;
  if (v > 0) {
    dir = 1;
  } else {
    dir = 0
  } 
  digitalWrite(l1, 1 ^ dir ^ MOTOR_LEFT_DIR);
  digitalWrite(l2, 1 ^ dir ^ MOTOR_LEFT_DIR);
  analogWrite(le, speed);
}