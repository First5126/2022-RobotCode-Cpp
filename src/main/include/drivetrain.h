#pragma once

#include "Layer.h"

namespace OutputDev {

    class DriveTrain {
        public:

            DriveTrain(Layer *layer);
            ~DriveTrain();

            void update();

        private:
            void Drive(double left, double right);
            Layer *m_layer;

            
    };
}