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

ShooterSubsystem::ShooterSubsystem()
{
    this->ShooterLeft  = new rev::CANSparkMax(31, rev::CANSparkMaxLowLevel::MotorType::kBrushless);
    this->ShooterRight = new rev::CANSparkMax(32, rev::CANSparkMaxLowLevel::MotorType::kBrushless);

   
    //this->ShooterLeft->SetInverted(true);

    this->m_shooter_encoder = new rev::SparkMaxRelativeEncoder {this->ShooterLeft->GetEncoder()}; 

}

ShooterSubsystem::~ShooterSubsystem() {
    
    free(this->ShooterLeft);
    free(this->ShooterRight);
}

void ShooterSubsystem::Periodic() {

}

void ShooterSubsystem::RunShooter(double speed) {
    this->m_pid.SetSetpoint(speed);

    double RunningSpeed = this->m_pid.Calculate(this->GetShooterSpeed());
    if (speed <= 0) RunningSpeed = 0;

    if (RunningSpeed < 0) RunningSpeed = 0;
    if (RunningSpeed > 1) RunningSpeed = 1;

    std::cout << "Running Speed: " << RunningSpeed << " --- " << this->GetShooterSpeed() << std::endl;

    this->ShooterLeft->Set(-RunningSpeed);
    this->ShooterRight->Set(-RunningSpeed);
}

double ShooterSubsystem::GetShooterSpeed() {
    return -m_shooter_encoder->GetVelocity();
}

bool ShooterSubsystem::IsShooterAtSpeed(double speed) {
    //bool at_speed = 0;

    return ( fabs(this->GetShooterSpeed() - speed) <= (speed * 0.03) );

    //return this->GetShooterSpeed() >= speed - (speed * 0.01);
}

void ShooterSubsystem::FeedBall() {
    this->FeederMotor.Set(-1);
}

void ShooterSubsystem::StopFeedBall() {
    this->FeederMotor.Set(0);
}

void ShooterSubsystem::StopAll() {
    this->StopFeedBall();
    this->RunShooter(0);
    this->shooter_speed = 0;
    m_pid.Reset();
}

bool ShooterSubsystem::ContainsBall() {
    uint32_t sensorValue = m_sensor.GetProximity();

    double sensorFlipped = fabs(2047 - sensorValue);

    return sensorFlipped < 1730;
}