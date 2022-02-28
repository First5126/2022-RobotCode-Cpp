#include "commands/DriveDistanceCommand.h"
#include <frc/smartdashboard/SmartDashboard.h>

#include <iostream>

DriveDistance::DriveDistance(DriveSubsystem* subsystem, std::function<double()> forward)
    : m_drive{subsystem},
    m_forward {std::move(forward)} {

    AddRequirements(m_drive);
}

void DriveDistance::Initialize() {
    this->is_done = 0;

    this->EncoderStartLeftValue = m_drive->GetLeftEncoderPos();
    this->EncoderStartRightValue = m_drive->GetRightEncoderPos();

    this->EncoderSetLeftValue = m_drive->CalcualteDriveEncoder(m_forward());
    this->EncoderSetRightValue = m_drive->CalcualteDriveEncoder(m_forward()); 

    
}

void DriveDistance::End(bool interrup)  {
    
    this->EncoderStartLeftValue = 0;
    this->EncoderStartRightValue = 0;

    this->EncoderSetLeftValue = 0;
    this->EncoderSetRightValue = 0;

    this->m_left_pid.Reset();
    this->m_right_pid.Reset();

    
}

void DriveDistance::Execute() {
    double RealEncoderLeft = this->EncoderSetLeftValue + this->EncoderStartLeftValue;
    double RealEncoderRight = this->EncoderSetRightValue + this->EncoderStartRightValue;

    this->m_left_pid.SetSetpoint(RealEncoderLeft);
    this->m_right_pid.SetSetpoint(RealEncoderRight);

    double driveLeft = this->m_left_pid.Calculate(this->m_drive->GetLeftEncoderPos());
    double driveRight = this->m_right_pid.Calculate(this->m_drive->GetRightEncoderPos());

    m_drive->TankDrive(driveLeft, driveRight);

    frc::SmartDashboard::PutNumber("Distance From Goal", RealEncoderLeft - this->m_drive->GetLeftEncoderPos());
    
}

bool DriveDistance::IsFinished() {
    double RealEncoderLeft = this->EncoderSetLeftValue + this->EncoderStartLeftValue;
    double RealEncoderRight = this->EncoderSetRightValue + this->EncoderStartRightValue;

    auto within =  [this](double within_amount, double first, double second) {
        double DiffernenceAmount = fabs(first - second);
        return within_amount >= DiffernenceAmount;
    };

    double WithinValue = 1000;
    if (within(WithinValue, m_drive->GetLeftEncoderPos() + m_drive->GetRightEncoderPos(), RealEncoderLeft + RealEncoderRight) && within(WithinValue, m_drive->GetRightEncoderPos(), RealEncoderRight)) {
        return true;
    }

    return false;
}