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
            static WPI_TalonFX *leftFront   = new WPI_TalonFX {2};
            static WPI_TalonFX *leftBack    = new WPI_TalonFX {4};
            static WPI_TalonFX *rightFront  = new WPI_TalonFX {8};
            static WPI_TalonFX *rightBack   = new WPI_TalonFX {6};
            

        }
    }
}