#include "interrupt_timer.h"


bool InterruptTimer::_expired = false;
TimerInterrupt* InterruptTimer::_timer = nullptr;


InterruptTimer::InterruptTimer(TimerInterrupt timer) {
  _timer = &timer;
}


bool InterruptTimer::expired() {
  return _expired;
}


void InterruptTimer::set(unsigned long intervalMs) {
  _expired = false;
  _timer->attachInterruptInterval(intervalMs, callback, intervalMs + 1);
}

static void InterruptTimer::callback() {
  if(!_expired) {
    _expired = true;
  }
}