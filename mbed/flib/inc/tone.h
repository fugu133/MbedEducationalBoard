#pragma once

#include "mbed.h"

#include <cmath>
#include <cstdio>

namespace fugu {
class Tone {
public:
  Tone(PinName _pin);
  void setup();
  void set_note(uint8_t note, uint8_t verocity);
  void set_frequency(float frq, float level);
  void free();
  bool isOperation();
  Tone &operator=(float frq) {
    this->set_frequency(frq, 0.5f);
    return *this;
  }

private:
  float convert_period_us(uint8_t note);
  float convert_duty_ratio(uint8_t verocity);
  void generate_period_table(float *period);
  void generate_duty_ratio_table(float *pulse_width);

  static constexpr uint32_t note_num = 128;

  PwmOut _sound_out;
  float note_to_period_us[note_num];
  float verocity_to_duty_ratio[note_num];
  bool _operation_flg;
};
} // namespace fugu