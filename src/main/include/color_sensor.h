#pragma once

#include <stdint.h>
#include <frc/I2C.h>
#include "rev/ColorSensorV3.h"

#include "Layer.h"


namespace InputDev {
    class ColorSensor {
        private:
            Layer* m_layer;
            rev::ColorSensorV3 m_sensor{frc::I2C::Port::kOnboard};

        public:

            ColorSensor(Layer *layer);
            ~ColorSensor();

            void OutputIntoLayer();

    };
}