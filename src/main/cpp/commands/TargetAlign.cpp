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
    
}

void TargetAlign::End(bool interrup)  {
    //this->m_drive->resetHeading();
    this->m_left_pid.Reset();
}

void TargetAlign::Execute() {


    frc::SmartDashboard::PutNumber("Distance From Goal", m_shooter->GetRobotAngleOffset());

    this->m_left_pid.SetSetpoint(0);

    double turning = this->m_left_pid.Calculate(m_shooter->GetRobotAngleOffset());

    units::voltage::volt_t volts (turning);

    double diff = fabs(m_shooter->GetRobotAngleOffset());

    std::cout << "TURNING: Diff: " << diff << "\t:\tVolts: " << volts.value() << std::endl; 

    this->m_drive->TankDriveVolts(-volts, volts);
}

bool TargetAlign::IsFinished() {
    double diff = fabs(m_shooter->GetRobotAngleOffset());

    return diff < 5;
}