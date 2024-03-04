#include "line_sensor.h"
#include "proximity_sensor.h"
#include "gyro.h"
#include "base_motor.h"
#include "ball_motor.h"

#define USE_TIMER_1 true
#define USE_TIMER_2 true
#include "TimerInterrupt.h"
#include <Keyboard.h>

Gyro gyro(ITimer1);
BaseMotor baseMotor;
BallMotor ballMotor;

void setup() {
  Serial.begin(9600);
  Serial.println("Start");
  baseMotor = BaseMotor();
  ballMotor = BallMotor();

  baseMotor.stopAll();
  ballMotor.stop();
}

void loop() {
  if (!Serial.available()) {
    return;
  }
  // Serial.println(gyro.readAngX());
  // delay(1000);

  String inputString = Serial.readStringUntil('\n');
  switch (inputString) {
    case "w":
      baseMotor.moveForward(12);
      break;
    case "s":
      baseMotor.moveBackward(12);
      break;
    case "a":
      baseMotor.turnLeft(12);
      break;
    case "d":
      baseMotor.turnRight(12);
      break;
    case "q":
      ballMotor.start();
      break;
    case "e":
      ballMotor.stop();
      break;
    default:
      baseMotor.stopAll();
      ballMotor.stop();
      break;
  }
}