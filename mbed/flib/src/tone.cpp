#include "../inc/tone.h"

namespace fugu {
Tone::Tone(PinName _pin) : _sound_out(_pin) { setup(); }

void Tone::setup() {
  free();
  generate_period_table(note_to_period_us);
  generate_duty_ratio_table(verocity_to_duty_ratio);
}

void Tone::set_note(uint8_t note, uint8_t verocity) {
  if (note & 0x80) {
    free();
  } else {
    _sound_out.period_us(note_to_period_us[note]);
    _sound_out.write(verocity_to_duty_ratio[verocity]);
    _operation_flg = true;
  }
}

void Tone::set_frequency(float frq, float level) {
  _sound_out.period_us(uint32_t(10e6f / frq));
  _sound_out.write(level);
}

void Tone::free() {
  _sound_out.write(0);
  _operation_flg = false;
}

bool Tone::isOperation() { return _operation_flg; }

float Tone::convert_period_us(uint8_t note) {
  note &= 0x7F;
  return (float)1e6 / (440.0f * powf(2.0f, ((float)(note - 69)) / 12.0f));
}
float Tone::convert_duty_ratio(uint8_t verocity) {
  verocity &= 0x7F;
  if (verocity)
    return log10f((float)verocity / 12.7f);
  else
    return 0;
}

void Tone::generate_period_table(float *period) {
  for (uint32_t num = 0; num < note_num; num++) {
    period[num] = convert_period_us(num);
  }
}

void Tone::generate_duty_ratio_table(float *pulse_width) {
  for (uint32_t num = 0; num < note_num; num++) {
    pulse_width[num] = convert_duty_ratio(num);
  }
}
} // namespace fugu