#include "../inc/imu_sensor.h"
#include "algorithm"
#include "iterator"
#include <cmath>
#include <cstdint>

namespace fugu {

IMUSensor::IMUSensor(I2C *i2c, uint8_t addr)
    : dev_i2c(i2c), dev_addr(addr),
      gyro_coeff(scale_convert(GyroScale::RANGE_250DPS)), gyro_bias{0},
      accel_coeff(scale_convert(AccelScale::RANGE_2G)), accel_bias{0} {
  write_byte(Register::PWR_MGMT_1, 0x00);
}

IMUSensor::IMUSensor(PinName sda, PinName scl, uint8_t addr)
    : dev_i2c(new I2C(sda, scl)), dev_addr(addr),
      gyro_coeff(scale_convert(GyroScale::RANGE_250DPS)), gyro_bias{0},
      accel_coeff(scale_convert(AccelScale::RANGE_2G)), accel_bias{0} {
  write_byte(Register::PWR_MGMT_1, 0x00);
}

bool IMUSensor::available() {
  uint8_t data = read_byte(Register::WHO_AM_I);
  return data == dev_addr >> 1;
}

bool IMUSensor::set_gyro_scale(GyroScale scale) {
  bool ack =
      write_byte(Register::GYRO_CONFIG, static_cast<uint8_t>(scale) << 3);
  gyro_coeff = scale_convert(scale);

  return ack;
}

bool IMUSensor::set_accel_scale(AccelScale scale) {
  bool ack =
      write_byte(Register::ACCEL_CONFIG, static_cast<uint8_t>(scale) << 3);
  accel_coeff = scale_convert(scale);

  return ack;
}

void IMUSensor::set_gyro_bias(const float (&bias)[3]) {
  std::copy(std::begin(bias), std::end(bias), std::begin(gyro_bias));
}

void IMUSensor::set_accel_bias(const float (&bias)[3]) {
  std::copy(std::begin(bias), std::end(bias), std::begin(accel_bias));
}

bool IMUSensor::read_angular_rate(float (&angular_rate)[3]) {
  uint8_t raw_data[6] = {0};
  bool ack;

  ack = !read_byte_array(Register::GYRO_XOUT_H, 6, raw_data);

  for (uint32_t i = 0; i < axsis_num; i++)
    angular_rate[i] =
        convert_angular_rate(raw_data + i * sizeof(int16_t)) - gyro_bias[i];

  return ack;
}

bool IMUSensor::read_acceleration(float (&acceleration)[3]) {
  uint8_t raw_data[6] = {0};
  bool ack;

  ack = !read_byte_array(Register::ACCEL_XOUT_H, 6, raw_data);

  for (uint32_t i = 0; i < axsis_num; i++)
    acceleration[i] =
        convert_acceleration(raw_data + i * sizeof(int16_t)) - accel_bias[i];

  return ack;
}

uint8_t IMUSensor::read_byte(uint8_t reg) {
  char write_data = reg;
  char read_data;

  dev_i2c->write(dev_addr, &write_data, 1, 1);
  dev_i2c->read(dev_addr, &read_data, 1, 0);

  return read_data;
}

bool IMUSensor::read_byte_array(uint8_t start_reg, uint8_t length,
                                uint8_t output[]) {
  char write_data = start_reg;

  dev_i2c->write(dev_addr, &write_data, 1, 1);
  return dev_i2c->read(dev_addr, reinterpret_cast<char *>(output), length, 0);
}

bool IMUSensor::write_byte(uint8_t reg, uint8_t data) {
  char write_data[2] = {reg, data};

  return dev_i2c->write(dev_addr, write_data, 2, 0);
}
} // namespace fugu