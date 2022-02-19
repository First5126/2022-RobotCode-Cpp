#pragma once

#include "Layer.h"
#include "robotbase.h"

namespace OutputDev {
    class Intake {
        private:

        Layer *m_layer;
        rev::CANSparkMax* IntakeMotor;

        public:

        Intake(Layer* layer);
        ~Intake();

        void update();
    };
}