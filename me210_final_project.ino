#include "line_sensor.h"
#include "proximity_sensor.h"
#include "gyro.h"
#include "base_motor.h"
#include "ball_motor.h"

#define USE_TIMER_1 true
#define USE_TIMER_2 true
#include "TimerInterrupt.h"

Gyro gyro(ITimer1);

void setup() {
  Serial.begin(9600);
  Serial.println("Start");
}

void loop() {
  Serial.println(gyro.readAngX());
  delay(1000);
}