#pragma once

#include "Layer.h"

namespace OutputDev {

    class DriveTrain {
        public:

        DriveTrain(CompLayer *layer);
        ~DriveTrain();

        void update();

        private:
        void Drive(double left, double right);
        CompLayer *m_layer;
    };
}