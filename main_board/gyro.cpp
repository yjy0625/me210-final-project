#include "gyro.h"
#include <Wire.h>
#include "Arduino.h"

#define GRYO_ADDR 0x68
#define GYRO_FREQ 100


float Gyro::dt;
int16_t Gyro::acX, Gyro::acY, Gyro::acZ, Gyro::gyX, Gyro::gyY, Gyro::gyZ, Gyro::temp, Gyro::gyXOS, Gyro::gyYOS, Gyro::gyZOS;
float Gyro::angX, Gyro::angY, Gyro::angZ;


Gyro::Gyro(TimerInterrupt timer) {
  Wire.begin();
  Wire.beginTransmission(GRYO_ADDR);
  Wire.write(0x6B);  
  Wire.write(0);    
  Wire.endTransmission(true);

  Serial.begin(9600);
  Serial.println("[gyro.cpp] Initialized gyro.");

  timer.init();
  timer.setFrequency(GYRO_FREQ * 2.0, update);

  dt = 1.0 / GYRO_FREQ;

  gyX = 0;
  gyY = 0;
  gyZ = 0;
  angX = 0;
  angY = 0;
  angZ = 0;
  temp = 0;
  Wire.beginTransmission(GRYO_ADDR);
  Wire.write(0x43);
  Wire.endTransmission(false);
  Wire.requestFrom(GRYO_ADDR, 6, true);
  gyXOS = Wire.read() << 8 | Wire.read();
  gyYOS = Wire.read() << 8 | Wire.read();
  gyZOS = Wire.read() << 8 | Wire.read();
}

static float Gyro::readAngX() {
  return angX;
}

static float Gyro::readAngY() {
  return angY;
}

static float Gyro::readAngZ() {
  return angZ;
}

static void Gyro::update() {
  angX += (gyX - gyXOS) * dt;
  angY += (gyY - gyYOS) * dt;
  angZ += (gyZ - gyZOS) * dt;
}