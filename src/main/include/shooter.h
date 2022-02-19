#pragma once

#include "Layer.h"
#include "robotbase.h"

namespace OutputDev {
    class Shooter {
        private:

        Layer *m_layer;
        TalonFX *ShooterMotor;

        TalonSRX *IntakeWheel;

        public:

        Shooter(Layer *layer);
        ~Shooter();

        void update();
    };
}