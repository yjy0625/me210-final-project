#include "line_sensor.h"
#include "proximity_sensor.h"
#include "constants.h"
#include "base_motor.h"
#include "line_sensor.h"
#include "proximity_sensor.h"
#include "arena_switch.h"
#include "interrupt_timer.h"

#define USE_TIMER_1 true
#define USE_TIMER_2 true
#define USE_TIMER_3 true
#include "TimerInterrupt.h"

BaseMotor* baseMotor = nullptr;
ProximitySensor* frontSensor = nullptr;
LineSensor* lineSensor = nullptr;
ArenaSwitch* arenaSwitch = nullptr;
InterruptTimer* timer = nullptr;

State state = Init;

void setup() {
  baseMotor = new BaseMotor(10, 13, 12, 6, 8, 9);
  lineSensor = new LineSensor(3, 4, 5);
  frontSensor = new ProximitySensor(7, 2, ITimer1);
  arenaSwitch = new ArenaSwitch(1);
  timer = new InterruptTimer(ITimer2);

  Serial.begin(9600);
  Serial.println("Start");
}

void loop() {
  switch(state) {
    case Init:
      // enter state machine
      state = S_A1;
      break;
    case S_A1:
      // robot initializes at start zone
      if(frontSensor->read() < A1_FRONT_SENSOR_THRESHOLD) {
        if(arenaSwitch->read()) {
          baseMotor->turnLeft(A1_BASE_TURN_VOLTAGE);
        }
        else {
          baseMotor->turnRight(A1_BASE_TURN_VOLTAGE);
        }
        state = S_A2;
      }
      else {
        if(arenaSwitch->read()) {
          baseMotor->turnRight(A1_BASE_TURN_VOLTAGE);
        }
        else {
          baseMotor->turnLeft(A1_BASE_TURN_VOLTAGE);
        }
        state = S_A3;
      }
      break;
    case S_A2:
      if(frontSensor->read() >= A1_FRONT_SENSOR_THRESHOLD) {
        if(arenaSwitch->read()) {
          baseMotor->turnLeft(A1_BASE_TURN_VOLTAGE);
        }
        else {
          baseMotor->turnRight(A1_BASE_TURN_VOLTAGE);
        }
        timer->set(A2_ROTATE_TIMER);
        state = S_A4;
      }
      break;
    case S_A3:
      if(frontSensor->read() < A1_FRONT_SENSOR_THRESHOLD) {
        if(arenaSwitch->read()) {
          baseMotor->turnLeft(A1_BASE_TURN_VOLTAGE);
        }
        else {
          baseMotor->turnRight(A1_BASE_TURN_VOLTAGE);
        }
        timer->set(A2_ROTATE_TIMER);
        state = S_A4;
      }
      break;
    case S_A4:
      if(timer->expired()) {
        baseMotor->moveForward(A4_BASE_FORWARD_VOLTAGE);
        state = S_A5;
      }
      break;
    case S_A5:
      if(lineSensor->dark(lineSensor->readLeftValue())) {
        state = S_A7;
      }
      break;
    case S_A6:
      if(timer->expired()) {
        baseMotor->moveForward(A6_BASE_FORWARD_VOLTAGE);
        state = S_A7;
      }
      break;
    case S_A7:
      if(lineSensor->light(lineSensor->readLeftValue())) {
        baseMotor->turnRight(A7_BASE_ROTATE_VOLTAGE);
        state = S_A8;
      }
      else if(lineSensor->light(lineSensor->readRightValue())) {
        baseMotor->turnLeft(A7_BASE_ROTATE_VOLTAGE);
        state = S_A6;
      }
    case S_A8:
      if(timer->expired()) {
        baseMotor->moveForward(A6_BASE_FORWARD_VOLTAGE);
        state = S_A7;
      }
      break;
    case S_B1:
      delay(1);
      break;
    case S_B2:
      delay(1);
      break;
    case S_B3:
      delay(1);
      break;
    case S_B4:
      delay(1);
      break;
    case S_C1:
      delay(1);
      break;
    case S_C2:
      delay(1);
      break;
    case S_C3:
      delay(1);
      break;
    case S_C4:
      delay(1);
      break;
    case S_C5:
      delay(1);
      break;
    case S_D1:
      delay(1);
      break;
    case S_D2:
      delay(1);
      break;
    case S_D3:
      delay(1);
      break;
    case S_D4:
      delay(1);
      break;
    case S_D5:
      delay(1);
      break;
    default:
      Serial.println("Warning: Unknown state!");
  }
}