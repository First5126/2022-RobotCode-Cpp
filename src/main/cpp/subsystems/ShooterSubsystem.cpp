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

    this->Hood = new rev::CANSparkMax(50, rev::CANSparkMaxLowLevel::MotorType::kBrushed);

    //this->Hood->SetInverted(true);
   
    //this->ShooterLeft->SetInverted(true);

    this->m_shooter_encoder = new rev::SparkMaxRelativeEncoder {this->ShooterRight->GetEncoder()}; 

    //this->m_hood_encoder = new rev::SparkMaxAlternateEncoder {this->Hood->GetAlternateEncoder(rev::CANEncoder::AlternateEncoderType::kQuadrature, 8196) };

    this->m_pid.SetTolerance(50);

}

ShooterSubsystem::~ShooterSubsystem() {
    
    free(this->ShooterLeft);
    free(this->ShooterRight);
}

void ShooterSubsystem::Periodic() {

}

void ShooterSubsystem::RunShooter(double speed) {
    this->m_pid.SetSetpoint(speed / 4096);

    
    double RunningSpeed = this->m_pid.Calculate(this->GetShooterSpeed() / 4096);
    if (speed <= 0) RunningSpeed = 0;

    if (RunningSpeed < 0) RunningSpeed = 0;
    if (RunningSpeed > 1) RunningSpeed = 1;

    std::cout << "Running Speed: " << RunningSpeed << " Target: " << speed << 
    " Current: " << this->GetShooterSpeed() << " Difference: " << this->GetShooterSpeed() - speed << std::endl;

    this->ShooterLeft->Set(-RunningSpeed);
    this->ShooterRight->Set(-RunningSpeed);
}

double ShooterSubsystem::GetShooterSpeed() {
    return -m_shooter_encoder->GetVelocity();
}

bool ShooterSubsystem::IsShooterAtSpeed(double speed) {
    //bool at_speed = 0;


    return ( fabs(this->GetShooterSpeed() - speed) <= 50 );

    //return this->GetShooterSpeed() >= speed - (speed * 0.01);
}

bool ShooterSubsystem::IsLimitReached() {
    return !this->hood_limit.Get();
}

void ShooterSubsystem::resetHood() {
    this->hood_encoder.Reset();
}

void ShooterSubsystem::SetHoodSpeed(double speed) {
    //if (this->IsLimitReached() && speed < 0) return;
    
   this->Hood->Set(speed); 
}  

int ShooterSubsystem::GetHoodPos() {
    return -this->hood_encoder.GetRaw();
}

void ShooterSubsystem::FeedBall() {
    this->FeederMotor.Set(-1);
}

void ShooterSubsystem::StopFeedBall() {
    this->FeederMotor.Set(0);
}

void ShooterSubsystem::SetHoodToPos(int pos) {

    if (this->IsLimitReached()) {
        this->ShooterReset = true;
        this->resetHood();
    }

    if (this->HasShooterBeenReset()) {
        double diff = fabs(pos - this->GetHoodPos());

        if (diff > 50) {
            if (pos > this->GetHoodPos()) {
                this->SetHoodSpeed( (diff > 400) ? -1 : -0.5);
            }
            else {
                this->SetHoodSpeed((diff > 400) ? 1 : 0.5);
            }
        }
        else {
            this->SetHoodSpeed(0);
            //std::cout << "Hood set to pos : " << this->GetHoodPos() << std::endl;
        }
    }
    else {
        std::cout << "RESETING..." << std::endl;
        if (!this->IsLimitReached()){
            this->SetHoodSpeed(1);
        }
    }

    
}

bool ShooterSubsystem::IsHoodAtPos(int pos) {
    double diff = fabs(pos - this->GetHoodPos());

    return (diff < 50);
}

void ShooterSubsystem::StopAll() {
    this->StopFeedBall();
    this->RunShooter(0);
    this->shooter_speed = 0;
    m_pid.Reset();
    this->SetHoodSpeed(0);
}

bool ShooterSubsystem::HasShooterBeenReset() {
    return this->ShooterReset;
}

bool ShooterSubsystem::ContainsBall() {
    uint32_t sensorValue = m_sensor.GetProximity();

    double sensorFlipped = fabs(2047 - sensorValue);

    return sensorFlipped < 1730 || !hopperball.Get();
}

void ShooterSubsystem::acuateServo(double angle) {
    m_pushy.Set(angle);
}