#pragma once

#include "mbed.h"
#include <cstdint>

namespace fugu {
class IMUSensor {
public:
  enum GyroScale : uint8_t {
    RANGE_250DPS = 0,
    RANGE_500DPS,
    RANGE_1000DPS,
    RANGE_2000DPS
  };

  enum AccelScale : uint8_t { RANGE_2G = 0, RANGE_4G, RANGE_8G, RANGE_16G };

  IMUSensor(I2C *i2c, uint8_t addr = default_dev_addr);
  IMUSensor(PinName sda, PinName scl, uint8_t addr = default_dev_addr);

  bool init();
  bool available();
  bool set_gyro_scale(GyroScale scale);
  bool set_accel_scale(AccelScale sclae);
  void set_gyro_bias(const float (&bias)[3]);
  void set_accel_bias(const float (&bias)[3]);
  bool read_acceleration(float (&acceleration)[3]);
  bool read_angular_rate(float (&angular_rate)[3]);
  

private:
  enum Register : uint8_t {
    GYRO_CONFIG = 0x1B,
    ACCEL_CONFIG = 0x1C,
    ACCEL_XOUT_H = 0x3B,
    ACCEL_XOUT_L = 0x3C,
    ACCEL_YOUT_H = 0x3D,
    ACCEL_YOUT_L = 0x3E,
    ACCEL_ZOUT_H = 0x3F,
    ACCEL_ZOUT_L = 0x40,
    GYRO_XOUT_H = 0x43,
    GYRO_XOUT_L = 0x44,
    GYRO_YOUT_H = 0x45,
    GYRO_YOUT_L = 0x46,
    GYRO_ZOUT_H = 0x47,
    GYRO_ZOUT_L = 0x48,
    PWR_MGMT_1 = 0x6B,
    WHO_AM_I = 0x75
  };

  I2C *dev_i2c;
  uint8_t dev_addr;
  float gyro_coeff;
  float gyro_bias[3];
  float accel_coeff;
  float accel_bias[3];

  static constexpr uint8_t default_dev_addr = 0x68 << 1;
  static constexpr float std_gravity = -9.80665f; // 標準重力加速度 [m/s^2]
  static constexpr uint8_t axsis_num = 3;

  uint8_t read_byte(uint8_t reg);
  bool read_byte_array(uint8_t start_reg, uint8_t length, uint8_t output[]);
  bool write_byte(uint8_t reg, uint8_t data);

  int16_t joint_i16(const uint8_t *data) {
    return static_cast<int16_t>(data[0] << 8 | data[1]);
  }

  float scale_convert(GyroScale scale) {
      constexpr float default_dps = 250;
      return default_dps * (static_cast<int32_t>(scale) + 1) / static_cast<float>(0x7FFF);
  }
  
  float scale_convert(AccelScale scale) {
      constexpr float default_g = 2;
      return std_gravity * default_g * (static_cast<int32_t>(scale) + 1) / static_cast<float>(0x7FFF);
  }

  float convert_acceleration(int16_t acc_raw) {
    return static_cast<float>(acc_raw) * accel_coeff;
  }

  float convert_acceleration(const uint8_t *data) {
    return convert_acceleration(joint_i16(data));
  }

  float convert_angular_rate(int16_t acc_raw) {
    return static_cast<float>(acc_raw) * gyro_coeff;
  }

  float convert_angular_rate(const uint8_t *data) {
    return convert_angular_rate(joint_i16(data));
  }
};
} // namespace fugu