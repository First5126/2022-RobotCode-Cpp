#pragma once

#include "Layer.h"
#include "ctre/Phoenix.h"


namespace Base {
    namespace Motors {
        namespace Misc {
            
        }

        namespace DriveTrain {
            TalonFX leftFront   = {2};
            TalonFX leftBack    = {4};
            TalonFX rightFront  = {8};
            TalonFX rightBack   = {6};

        }
    }
}