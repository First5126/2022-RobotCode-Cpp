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
            static TalonFX *leftFront   = new TalonFX {2};
            static TalonFX *leftBack    = new TalonFX {4};
            static TalonFX *rightFront  = new TalonFX {8};
            static TalonFX *rightBack   = new TalonFX {6};
            

        }
    }
}