#pragma once

#include <stdint.h>

#include "Layer.h"
#include <frc2/command/PIDSubsystem.h>

namespace Auto {
    class BallTarget {
        private:
            Layer* m_layer;
            frc2::PIDController m_pidController{0, 0, 0};

            

        public:
            BallTarget(Layer *layer);
            ~BallTarget();

            void update();
            void OutputIntoLayer();
    };
}