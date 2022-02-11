#pragma once

#include "Layer.h"
#include <stdint.h>
#include <frc/XboxController.h>


namespace InputDev {
    class Xbox {
        private:
        Layer* m_layer;

        public:

        frc::XboxController* m_controller;

        Xbox(Layer *layer);
        Xbox(Layer *layer, uint8_t port);
        ~Xbox();

        void OutputIntoLayer();

        private:

        double ClampDeadZone(double intput, double deadzone);
    };
} 