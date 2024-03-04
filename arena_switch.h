#ifndef arena_switch_h
#define arena_switch_h

#include "Arduino.h"


class ArenaSwitch {
public:
	ArenaSwitch(int inputPin);
	bool read();
	uint8_t readMidValue();
	uint8_t readRightValue();
private:
	int _inputPin;
};

#endif