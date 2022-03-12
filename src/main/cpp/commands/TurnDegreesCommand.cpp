
#include "commands/TurnDegreesCommand.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "units/voltage.h"

#include <iostream>

TurnDegrees::TurnDegrees(DriveSubsystem* subsystem, std::function<double()> turn) 
 : m_drive {subsystem}
 , m_turn {std::move(turn)} {

}

void TurnDegrees::Initialize() {
    this->is_done = 0;
    this->m_drive->resetHeading();
    
}

void TurnDegrees::End(bool interrup)  {
    this->m_drive->resetHeading();
    this->m_left_pid.Reset();
}

void TurnDegrees::Execute() {


    frc::SmartDashboard::PutNumber("Distance From Goal", 0);


    this->m_left_pid.SetSetpoint(m_turn());

    double turning = this->m_left_pid.Calculate(this->m_drive->GetHeading());

    units::voltage::volt_t volts (turning);

    double diff = fabs(this->m_drive->GetHeading() - m_turn());

    std::cout << "TURNING: Diff: " << diff << "\t:\tVolts: " << volts.value() << std::endl; 

    this->m_drive->TankDriveVolts(volts, -volts);
}

bool TurnDegrees::IsFinished() {
    double diff = fabs(this->m_drive->GetHeading() - m_turn());

    return diff < 2;
}