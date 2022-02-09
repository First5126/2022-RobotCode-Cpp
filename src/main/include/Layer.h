#pragma once

#include <frc/smartdashboard/SmartDashboard.h>

namespace RobotMode {
    enum mode {
        AUTO = 0,
        TELEOP,
        DISABLED,
        TEST
    };
}

class CompLayer {
    public:

    CompLayer();
    ~CompLayer();

    const static int test = 0;

    // Values Layer Contains
    double forward_drive_speed = 0;
    double turning_drive_speed = 0;

    void OutputToSmartdashboard(); //{
        //frc::SmartDashboard::PutNumber("Forward Drive Speed", forward_drive_speed);
        //frc::SmartDashboard::PutNumber("Turning Drive Speed", turning_drive_speed);
    //}

    
};