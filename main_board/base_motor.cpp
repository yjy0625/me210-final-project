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

void BaseMotor::switchLeftRight() {
  swap(le, re);
  swap(l1, r1);
  swap(l2, r2);
}

void BaseMotor::setVoltages(float vl, float vr) {
  setLeftVoltage(vl);
  setRightVoltage(vr);
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
  // // Serial.print("Setting right voltage to ");
  // // Serial.println(v);
  digitalWrite(r1, 1 ^ dir ^ MOTOR_RIGHT_DIR);
  digitalWrite(r2, 0 ^ dir ^ MOTOR_RIGHT_DIR);
  analogWrite(re, speed);

  return;

  // Serial.print("Setting digital pin");
  // Serial.println(r1);
  // Serial.println(1 ^ dir ^ MOTOR_RIGHT_DIR);
  // Serial.println(digitalRead(r1));

  // Serial.print("Setting digital pin");
  // Serial.println(r2);
  // Serial.println(0 ^ dir ^ MOTOR_RIGHT_DIR);
  // Serial.println(digitalRead(r2));

  // Serial.print("Setting analog pin");
  // Serial.println(re);
  // Serial.println(speed);
  // Serial.println(analogRead(re));
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
  // // Serial.print("Setting left voltage to ");
  // // Serial.println(v);
  digitalWrite(l1, 1 ^ dir ^ MOTOR_LEFT_DIR);
  digitalWrite(l2, 0 ^ dir ^ MOTOR_LEFT_DIR);
  analogWrite(le, speed);

  return;

  // Serial.print("Setting digital pin");
  // Serial.println(l1);
  // Serial.println(1 ^ dir ^ MOTOR_LEFT_DIR);
  // Serial.println(digitalRead(l1));

  // Serial.print("Setting digital pin");
  // Serial.println(l2);
  // Serial.println(0 ^ dir ^ MOTOR_LEFT_DIR);
  // Serial.println(digitalRead(l2));

  // Serial.print("Setting analog pin");
  // Serial.println(le);
  // Serial.println(speed);
  // Serial.println(analogRead(le));
}

