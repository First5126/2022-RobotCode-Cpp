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

    m_left_pid.SetTolerance(1);
    m_right_pid.SetTolerance(1);

    this->m_left_pid.SetSetpoint(RealEncoderLeft / 4096);
    this->m_right_pid.SetSetpoint(RealEncoderRight / 4096 );

    double driveLeft = this->m_left_pid.Calculate(this->m_drive->GetLeftEncoderPos() / 4096);
    double driveRight = this->m_right_pid.Calculate(this->m_drive->GetRightEncoderPos() / 4096);

    driveLeft = std::clamp(driveLeft, -10., 10.);
    driveRight = std::clamp(driveRight, -10., 10.);

    std::cout << "SPEED: " << driveLeft << ", " << driveRight << " --> " << RealEncoderLeft - this->m_drive->GetLeftEncoderPos() << std::endl;

    units::voltage::volt_t leftvolt (driveLeft);
    units::voltage::volt_t rightvolt (driveRight);

    m_drive->TankDriveVolts(leftvolt, leftvolt);

    frc::SmartDashboard::PutNumber("Distance From Goal", RealEncoderLeft - this->m_drive->GetLeftEncoderPos());
    
}

bool DriveDistance::IsFinished() {
    double RealEncoderLeft = this->EncoderSetLeftValue + this->EncoderStartLeftValue;
    double RealEncoderRight = this->EncoderSetRightValue + this->EncoderStartRightValue;

    auto within =  [this](double within_amount, double first, double second) {
        double DiffernenceAmount = fabs(first - second);
        return within_amount >= DiffernenceAmount;
    };

    double WithinValue = 2000;
    if (within(WithinValue, m_drive->GetLeftEncoderPos(), RealEncoderLeft)) {
        ThereAccum++;
    }
    else {
        ThereAccum = 0;
    }

    return ThereAccum > 10;
    
}