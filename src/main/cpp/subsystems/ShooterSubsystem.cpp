/*
* TEAM 5126 (c) : 2022 FRC Rapid React
* Command Based C++ Robot Code 
* 
* [Shooter]
* 
*       0
*  |O    
* [=====] 
* 
* ## What does this subsystem do?
* This subsystem can set the speed of the fly wheel.
* It can also Feed the balls into the shooter.
*/ 

#include "subsystems/ShooterSubsystem.h"

#include <iostream>

ShooterSubsystem::ShooterSubsystem() {
    this->ShooterLeft  = new rev::CANSparkMax(0, rev::CANSparkMaxLowLevel::MotorType::kBrushless);
    this->ShooterRight = new rev::CANSparkMax(0, rev::CANSparkMaxLowLevel::MotorType::kBrushless);

    std::cout << "Shooter Subsystem - " << "Checking motors..." << std::endl;

    assert(this->ShooterLeft != nullptr);
    assert(this->ShooterRight != nullptr);

    std::cout << "\tSparkMax\tOK" << std::endl;

    assert(&this->FeederMotor != nullptr);

    std::cout << "\tTalonSRX\tOK" << std::endl;

    bool motors_ok = 
        this->ShooterLeft->GetBusVoltage() > 0 &&
        this->ShooterRight->GetBusVoltage() > 0 &&
        this->FeederMotor.GetBusVoltage() > 0;

    std::cout << "\tMOTORS\t" << (motors_ok ? "OK" : "FAIL") << std::endl;

    this->ShooterRight->Follow(*this->ShooterLeft);
    this->ShooterRight->SetInverted(true);

    m_pid.SetPID(Shooter_Kp, Shooter_Ki, Shooter_Kd);

}

void ShooterSubsystem::Periodic() {

}

void ShooterSubsystem::RunShooter(double speed) {
    m_pid.SetSetpoint(speed);

    auto ShooterSpeed = m_pid.Calculate(this->GetShooterSpeed());

    this->ShooterLeft->Set(ShooterSpeed);
}

double ShooterSubsystem::GetShooterSpeed() {
    return this->ShooterLeft->GetEncoder().GetVelocity();
}

bool ShooterSubsystem::IsShooterAtSpeed(double speed) {
    return this->GetShooterSpeed() >= speed;
}

void ShooterSubsystem::FeedBall() {
    this->FeederMotor.Set(1);
}

void ShooterSubsystem::StopFeedBall() {
    this->FeederMotor.Set(0);
}

void ShooterSubsystem::StopAll() {
    this->StopFeedBall();
    this->RunShooter(0);
    this->ShooterLeft->Set(0);
}