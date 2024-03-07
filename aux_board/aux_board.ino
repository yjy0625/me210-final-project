#include "ball_motor.h"
#include <Arduino.h>

#define BALL_MOTOR_CONTROL_PIN A0
#define ON_PIN A2

BallMotor ballMotor;

void setup()
{
    Serial.begin(9600);
    pinMode(BALL_MOTOR_CONTROL_PIN, INPUT);
    pinMode(ON_PIN, OUTPUT);
    analogWrite(ON_PIN, 1000);
    ballMotor.stop();
}

void loop()
{
    int sensorValue = analogRead(BALL_MOTOR_CONTROL_PIN);
    if (sensorValue > 500)
    {
        ballMotor.start();
    }
    else
    {
        ballMotor.stop();
    }
    if (Serial) {
        Serial.println(sensorValue);
    }
}