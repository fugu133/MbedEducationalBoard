#pragma once

#include "mbed.h"

namespace fugu {
    class SwitchStatus {
public:
  SwitchStatus(PinName pin);
  void mode(PinMode pull_mode = PullDefault);
  void startSampring(uint32_t us = 30000);
  bool read();
  bool longPressRead(uint32_t th, bool reset = false);


private:
  void sampling_handler();
  DigitalIn _sw;
  Ticker _sampling;
  bool _logic_mode;
  uint32_t _read_val;
  uint32_t _sampling_time_us;
};
}