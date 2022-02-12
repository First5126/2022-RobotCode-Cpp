#pragma once

#include "Layer.h"
#include "ctre/Phoenix.h"
#include "rev/ColorSensorV3.h"
#include "rev/CANSparkMax.h"


namespace Base {
    namespace Motors {
        namespace Misc {
            
        }

        namespace DriveTrain {
            TalonFX leftFront   = {2};
            TalonFX leftBack    = {4};
            TalonFX rightFront  = {8};
            TalonFX rightBack   = {6};

            rev::CANSparkMax Shooter(3, rev::CANSparkMaxLowLevel::MotorType::kBrushless);

        }
    }
}