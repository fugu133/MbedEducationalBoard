#include "../inc/switch_status.h"

namespace fugu {
    SwitchStatus::SwitchStatus(PinName pin) : _sw(pin), _read_val(0){
  mode(PullDown);
  startSampring();
}


void SwitchStatus::startSampring(uint32_t us) {
  _sampling_time_us = us;
  _sampling.attach_us(callback(this, &SwitchStatus::sampling_handler),
                     _sampling_time_us);
}

void SwitchStatus::mode(PinMode pull_mode) {
    _logic_mode = (pull_mode == PullUp);
    _sw.mode(pull_mode);
}

bool SwitchStatus::read() { return _read_val; }

bool SwitchStatus::longPressRead(uint32_t th, bool reset) {
    bool return_val = _read_val >= th;
    _read_val = (return_val && reset) ? 0 : _read_val;
    return return_val;
}

void SwitchStatus::sampling_handler() {
    bool now_val = _logic_mode ? !_sw.read() : _sw.read();
    _read_val = now_val ? (_read_val+1) : 0;
}
}