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

void BaseMotor::setLeftVoltage(float v) {
  v = constrain(v, 0, 12); 
  if (v > 0) {
    digitalWrite(r1, 1);
    digitalWrite(r2, 0);
  }
  else if (v < 0) {
    digitalWrite(r1, 0);
    digitalWrite(r2, 1);
  }
  else {
    analogWrite(re, 0);
    return;
  }
  analogWrite(re, map(abs(v), 0, 12, 0, 255));
}

void BaseMotor::setRightVoltage(float v) {
  v = v * 1.166;
  v = constrain(v, 0, 12); 
  if (v > 0) {
    digitalWrite(l1, 1);
    digitalWrite(l2, 0);
  } else if (v < 0) {
    digitalWrite(l1, 0);
    digitalWrite(l2, 1);
  } else {
    analogWrite(le, 0);
    return;
  }
  analogWrite(le, map(abs(v), 0, 12, 0, 255));
}