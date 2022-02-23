#pragma once

#include "Layer.h"
#include "robotbase.h"

namespace OutputDev {
    class Shooter {
        private:

        Layer *m_layer;
        TalonFX *ShooterMotorRight;
        TalonFX * ShooterMotorLeft;

        TalonSRX *IntakeWheel;

        public:

        Shooter(Layer *layer);
        ~Shooter();

        void update();
        void VelUpdate();
    };
}