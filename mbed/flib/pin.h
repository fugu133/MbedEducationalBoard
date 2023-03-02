#pragma once

#include "mbed.h"

namespace fugu {
    namespace {

        /* I2C通信バスピン */
        constexpr PinName i2c_sda = p9;
        constexpr PinName i2c_scl = p10;
        
        /* ポテンショメータアナログ入力ピン */
        constexpr PinName vr_ain1 = p15;
        constexpr PinName vr_ain2 = p16;
        constexpr PinName vr_ain3 = p17;

        /* 外部GPIOピン */
        constexpr PinName ext_gpio1 = p20;
        constexpr PinName ext_gpio2 = p19;
        constexpr PinName ext_gpio3 = p18;

        /* モータドライバPWM入力ピン */
        constexpr PinName drv_pwm_out_a1 = p21;
        constexpr PinName drv_pwm_out_a2 = p22;
        constexpr PinName drv_pwm_out_b1 = p23;
        constexpr PinName drv_pwm_out_b2 = p24;

        /* ピエゾサウンダPWM出力ピン */
        constexpr PinName spk_pwm_out = p25;

        /* タクトスイッチ論理入力ピン */
        constexpr PinName sw_in1 = p30;
        constexpr PinName sw_in2 = p29;
        constexpr PinName sw_in3 = p28;
        constexpr PinName sw_in4 = p27;
        
    }
}

