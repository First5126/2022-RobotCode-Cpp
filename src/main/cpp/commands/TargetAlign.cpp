#include "commands/TargetAlign.h"
#include "commands/DriveDistanceCommand.h"

#include "frc2/command/SequentialCommandGroup.h"


#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>

#include <frc/smartdashboard/SmartDashboard.h>

#include <iostream>

TargetAlign::TargetAlign(ShooterSubsystem* shooter, DriveSubsystem* drive)
    : m_shooter{shooter}
    , m_drive{drive} {

    //this->AddCommands( DriveDistance (m_subsystem, [this]() { return 10.0; }));
    
}

void TargetAlign::Initialize() {
    this->is_done = 0;
    //this->m_drive->resetHeading();
    this->m_left_pid.Reset();
    this->m_left_pid.SetSetpoint(0);

    
}

void TargetAlign::End(bool interrup)  {
    //this->m_drive->resetHeading();
    this->m_left_pid.Reset();
    this->m_left_pid.SetSetpoint(0);
}

void TargetAlign::Execute() {
    
    frc::SmartDashboard::PutNumber("Distance From Goal", m_shooter->GetRobotAngleOffset());

    //units::voltage::volt_t TurningPower (turning);
    //frc::SmartDashboard::PutNumber("Target Align Volts", TurningPower.value());
    //std::cout << "Output: " << TurningPower.value() << std::endl;

    int TurningPower = 0;

    if (m_shooter->GetRobotAngleOffset() > 0) {
        TurningPower = 0.35;
    }
    else {
        TurningPower = -0.35;
    }

    this->m_drive->TankDrive(TurningPower, -TurningPower);
}

bool TargetAlign::IsFinished() {
    double diff = fabs(m_shooter->GetRobotAngleOffset());

    return diff < 5 || m_shooter->GetCommandState();
}