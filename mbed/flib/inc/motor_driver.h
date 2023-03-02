#pragma once

#include "mbed.h"
#include <cmath>
#include <cstdint>
#include <utility>

namespace fugu {
    class MotorDriver {
        public:
        enum Direction : uint8_t {
            FORWARD,
            REVERSE,
            COAST,
            BREAKE,
        };

        MotorDriver(PinName in1, PinName in2);
        void set_frequency(uint32_t frq);
        void write(Direction dir, float abs_speed);
        void write(float speed);

        MotorDriver &operator= (float speed) {
            write(speed);
            return *this;
        }

        private:
        PwmOut drv_in1, drv_in2;
        void pwm_write(float duty1, float duty2);
    };
}