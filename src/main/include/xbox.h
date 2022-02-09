#pragma once

#include "Layer.h"
#include <stdint.h>
#include <frc/XboxController.h>


namespace Input {
    class Xbox {
        private:
        CompLayer* m_layer;

        public:

        frc::XboxController* m_controller;

        Xbox(CompLayer *layer);
        Xbox(CompLayer *layer, uint8_t port);
        ~Xbox();

        void OutputIntoLayer();
    };
} 