#include "proximity_sensor.h"
#include "Arduino.h"


ProximitySensor::ProximitySensor(int outputPin, int inputPin, TimerInterrupt timer) {
  _outputPin = outputPin;
  _inputPin = inputPin;

  cnt = 0;
  on = 1;

  timer.init();
  timer.setFrequency(1000 * 2, update);
  Serial.begin(9600);
  pinMode(outputPin, OUTPUT);
  pinMode(inputPin, INPUT);
}

float ProximitySensor::read() {
  float duration = pulseIn(_inputPin, HIGH);
  return duration / 58;
}

static void ProximitySensor::update() {
  if(cnt % period == 0) {
    cnt %= period;
  }
  if(cnt < thres && on == 0) {
    digitalWrite(_outputPin, 1);
    on = 1;
  }
  else if(cnt >= thres && on == 1) {
    digitalWrite(_outputPin, 0);
    on = 0;
  }
  cnt++;
}