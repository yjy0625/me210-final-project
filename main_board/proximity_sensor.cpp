#include "proximity_sensor.h"
#include "Arduino.h"


int ProximitySensor::_outputPin, ProximitySensor::_inputPin;
int ProximitySensor::cnt, ProximitySensor::on;


ProximitySensor::ProximitySensor(int outputPin, int inputPin) {
  _outputPin = outputPin;
  _inputPin = inputPin;
}

void ProximitySensor::init(TimerInterrupt &timer) {
  cnt = 0;
  on = 1;

  timer.init();
  timer.setFrequency(1000 * 2, update);
  pinMode(_outputPin, OUTPUT);
  pinMode(_inputPin, INPUT);
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