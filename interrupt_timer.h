#ifndef interrupt_timer_h
#define interrupt_timer_h

#include "Arduino.h"
#include "TimerInterrupt.hpp"


class InterruptTimer {
public:
	InterruptTimer(TimerInterrupt timer);
	void set(unsigned long intervalMs);
	bool expired();
private:
	static bool _expired;
	static TimerInterrupt* _timer;
	static void callback();
};

#endif