#include "base_motor.h"

BaseMotor::BaseMotor(int leftEn, int leftIn1, int leftIn2, int rightEn, int rightIn1, int rightIn2) {
  le = leftEn;
  l1 = leftIn1;
  l2 = leftIn2;
  re = rightEn;
  r1 = rightIn1;
  r2 = rightIn2;
  left_dir = 1;
  right_dir = 0;
  switching = false;

  pinMode(le, OUTPUT);
  pinMode(re, OUTPUT);
  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
}

void BaseMotor::switchLeftRight() {
  switching = true;
  // swap(le, re);
  // swap(l1, r1);
  // swap(l2, r2);
  // left_dir = 0;
  // right_dir = 1;
}

void BaseMotor::swap(int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
}

void BaseMotor::setVoltages(float vl, float vr) {
  if(switching) {
    setLeftVoltage(vr);
    setRightVoltage(vl);
  }
  else {
    setLeftVoltage(vl);
    setRightVoltage(vr);
  }
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
  setLeftVoltage(-v + TURN_SIDE_FAR_DELTA);
  setRightVoltage(v + TURN_SIDE_NEAR_DELTA);
  // Serial.println("Turning left");
  // Serial.println(v);
  // Serial.println(-v + TURN_SIDE_FAR_DELTA);
  // Serial.println(v + TURN_SIDE_NEAR_DELTA);
}

void BaseMotor::turnRight(float v) {
  setLeftVoltage(v + TURN_SIDE_NEAR_DELTA);
  setRightVoltage(-v + TURN_SIDE_FAR_DELTA);
  // Serial.println("Turning right");
  // Serial.println(v);
  // Serial.println(v + TURN_SIDE_NEAR_DELTA);
  // Serial.println(-v + TURN_SIDE_FAR_DELTA);
}

void BaseMotor::stopAll() {
  setLeftVoltage(0);
  setRightVoltage(0);
}

void BaseMotor::turnLeftPrimitive() {
  setLeftVoltage(-12.0);
  setRightVoltage(9.0);
}

void BaseMotor::turnRightPrimitive() {
  setLeftVoltage(9.0);
  setRightVoltage(-12.0);
}

void BaseMotor::turnLeftSlowPrimitive() {
  setLeftVoltage(-9.0);
  setRightVoltage(6.0);
}

void BaseMotor::turnRightSlowPrimitive() {
  setLeftVoltage(6.0);
  setRightVoltage(-9.0);
}

void BaseMotor::turnLeftFixedBlock() {
  turnLeftPrimitive();
  delay(800);
  stopAll();
}

void BaseMotor::turnRightFixedBlockAgainstContactZone() {
  turnLeftPrimitive();
  delay(CONTACT_TURN_TIME);

  turnRightPrimitive();
  delay(CONTACT_TURN_TIME);

  turnRightPrimitive();
  delay(CONTACT_TURN_TIME);
  stopAll();
}

void BaseMotor::turnLeftFixedBlockShootingZone() {
  setLeftVoltage(-12.0);
  setRightVoltage(12.0);
  delay(CONTACT_TURN_TIME / 2);
  moveForward(10.0);
  delay(400);
  setLeftVoltage(-12.0);
  setRightVoltage(12.0);
  delay(int(0.65 * CONTACT_TURN_TIME / 2));
  stopAll();
}

void BaseMotor::setRightVoltage(float v) {
  v = v * MOTOR_SCALE;
  v = constrain(v, -12, 12); 
  int speed = map(abs(v), 0, 12, 0, 255);
  if (abs(v) < EPS){
    analogWrite(re, 0);
    digitalWrite(r1, 0);
    digitalWrite(r2, 0);
    return;
  }
  int dir;
  if (v > 0) {
    dir = 1;
  } else {
    dir = 0;
  }
  // if(Serial) {
  //   Serial.print("Setting right voltage to ");
  //   Serial.println(1 ^ dir ^ right_dir);
  // }
  digitalWrite(r1, 1 ^ dir ^ right_dir);
  digitalWrite(r2, 0 ^ dir ^ right_dir);
  analogWrite(re, speed);

  return;
}

void BaseMotor::setLeftVoltage(float v) {
  v = v * MOTOR_SCALE;
  v = constrain(v, -12, 12); 
  int speed = map(abs(v), 0, 12, 0, 255);
  if (abs(v) < EPS){
    analogWrite(le, 0);
    digitalWrite(l1, 0);
    digitalWrite(l2, 0);
    return;
  }
  int dir;
  if (v > 0) {
    dir = 1;
  } else {
    dir = 0;
  } 
  // if(Serial) {
  //   Serial.print("Setting left voltage to ");
  //   Serial.println(1 ^ dir ^ left_dir);
  // }
  digitalWrite(l1, 1 ^ dir ^ left_dir);
  digitalWrite(l2, 0 ^ dir ^ left_dir);
  analogWrite(le, speed);

  return;
}

