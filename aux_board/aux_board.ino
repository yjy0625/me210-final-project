#include "ball_motor.h"
#include <Arduino.h>

#define BALL_MOTOR_CONTROL_PIN A0
// #define ON_PIN A2
#define SWITCH_PIN 8
#define SWITCH_OUT_PIN A5
#define MAIN_BOARD_RECEIVE_PIN A4
#define MAIN_BOARD_SWITCH_AVAILABLE_PIN 11
#define DIODE_YES_OUT_PIN 12
#define DIODE_NO_OUT_PIN 13

BallMotor ballMotor;

void setup()
{
    Serial.begin(9600);
    pinMode(BALL_MOTOR_CONTROL_PIN, INPUT);
    pinMode(SWITCH_PIN, INPUT);
    pinMode(SWITCH_OUT_PIN, OUTPUT);
    pinMode(MAIN_BOARD_SWITCH_AVAILABLE_PIN, INPUT);
    pinMode(MAIN_BOARD_RECEIVE_PIN, INPUT);
    pinMode(DIODE_YES_OUT_PIN, OUTPUT);
    pinMode(DIODE_NO_OUT_PIN, OUTPUT);
    // pinMode(ON_PIN, OUTPUT);
    // analogWrite(ON_PIN, 1000);
    ballMotor.stop();

    digitalWrite(DIODE_NO_OUT_PIN, 0);
    digitalWrite(DIODE_YES_OUT_PIN, 0);
}

void loop()
{
    // Serial.println(digitalRead(SWITCH_PIN));
    if(digitalRead(SWITCH_PIN) == 1) {
      // Serial.println("high");
      analogWrite(SWITCH_OUT_PIN, 1000);
    }
    else {
      // Serial.println("low");
      analogWrite(SWITCH_OUT_PIN, 0);
    }

    if (Serial) {
      Serial.println(digitalRead(MAIN_BOARD_SWITCH_AVAILABLE_PIN));
    }
    if(digitalRead(MAIN_BOARD_SWITCH_AVAILABLE_PIN)) {
      if(digitalRead(MAIN_BOARD_RECEIVE_PIN)) {
        // Serial.println("high");
        digitalWrite(DIODE_YES_OUT_PIN, 1);
        digitalWrite(DIODE_NO_OUT_PIN, 0);
      }
      else {
        // Serial.println("low");
        digitalWrite(DIODE_YES_OUT_PIN, 0);
        digitalWrite(DIODE_NO_OUT_PIN, 1);
      }
    } 
    else {
      digitalWrite(DIODE_YES_OUT_PIN, 0);
      digitalWrite(DIODE_NO_OUT_PIN, 0);
    }

    int sensorValue = analogRead(BALL_MOTOR_CONTROL_PIN);
    if (sensorValue > 500) {
        ballMotor.start();
    }
    else {
        ballMotor.stop();
    }
    // if (Serial) {
    //     Serial.println(sensorValue);
    // }
}