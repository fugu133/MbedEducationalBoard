#include "../inc/motor_driver.h"

namespace fugu {

MotorDriver::MotorDriver(PinName in1, PinName in2) : drv_in1(in1), drv_in2(in2) {
    static constexpr uint32_t default_pulse_frequensy = 1'000;
    set_frequency(default_pulse_frequensy);
    write(Direction::COAST, 0);
}

void MotorDriver::set_frequency(uint32_t frq) {
  float period = 1.f / frq;

  drv_in1.period(period);
  drv_in2.period(period);
}

void MotorDriver::write(Direction dir, float abs_speed) {
  switch (dir) {
  case Direction::FORWARD:
    pwm_write(abs_speed, 0);
    break;
  case Direction::REVERSE:
    pwm_write(0, abs_speed);
    break;
  case Direction::COAST:
    pwm_write(0, 0);
    break;
  case Direction::BREAKE:
    pwm_write(1, 1);
    break;
  }
}

void MotorDriver::write(float speed) {
  if (std::abs(speed) <= std::numeric_limits<float>::epsilon())
    write(Direction::BREAKE, 0);
  else if (std::signbit(speed))
    write(Direction::REVERSE, std::abs(speed));
  else
    write(Direction::FORWARD, speed);
}

void MotorDriver::pwm_write(float duty1, float duty2) {
  drv_in1.write(duty1);
  drv_in2.write(duty2);
}
} // namespace fugu