#pragma once

#include "Layer.h"
#include <frc/drive/DifferentialDrive.h>

namespace OutputDev {

    class DriveTrain {
        public:

            DriveTrain(Layer *layer);
            ~DriveTrain();

            void update();

        private:
            void Drive(double left, double right);
            Layer *m_layer;


            frc::DifferentialDrive *m_drive;
            
    };
}