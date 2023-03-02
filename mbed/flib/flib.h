#pragma once

#include "inc/switch_status.h"
#include "inc/PowerControl/EthernetPowerControl.h"
#include "inc/imu_sensor.h"
#include "inc/motor_driver.h"
#include "inc/tone.h"
#include "pin.h"


namespace fugu {
    namespace {
        void init() { PHY_PowerDown(); }
    }
} // namespace fugu
