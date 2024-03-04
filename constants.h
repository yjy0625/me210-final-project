#ifndef constants_h
#define constants_h

#include "Arduino.h"

typedef enum {
  Init,
  S_A1, S_A2, S_A3, S_A4, S_A5, S_A6, S_A7, S_A8,
  S_B1, S_B2, S_B3, S_B4,
  S_C1, S_C2, S_C3, S_C4, S_C5,
  S_D1, S_D2, S_D3, S_D4, S_D5
} State;

#define A1_FRONT_SENSOR_THRESHOLD     5.0
#define A1_BASE_TURN_VOLTAGE          6.0
#define A2_ROTATE_TIMER               2000
#define A4_BASE_FORWARD_VOLTAGE       6.0
#define A6_BASE_TURN_VOLTAGE          6.0
#define A6_BASE_FORWARD_VOLTAGE       1000
#define A7_BASE_ROTATE_VOLTAGE        6.0

#endif