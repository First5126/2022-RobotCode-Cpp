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
#include "frc/smartdashboard/SmartDashboard.h"

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
    frc::SmartDashboard::PutBoolean("Ball in Shooter", this->ContainsBall());
    frc::SmartDashboard::PutNumber("Robot Distance", m_vision.GetTapeDistance());

    if (m_vision.IsDetectingTape()) {
        double CurrentDistance = m_vision.GetTapeDistance();

        double DistanceDelta = 1000;
        int closestPoint = -1;

        for (int i = 0; i < TABLESIZE; i ++) {
            int distance = this->distanceTable[i];
            double delta = fabs(distance - CurrentDistance);

            if (delta <= DistanceDelta) {
                DistanceDelta = delta;
                closestPoint = i; 
            }
        }

        HoodSetpoint = this->HoodTable[closestPoint];
        SpeedSetPoint = this->SpeedTable[closestPoint];

        if (closestPoint + 1 < TABLESIZE ) {
            int DiffSpeedSetpoint = this->SpeedTable[closestPoint + 1];
            int DiffHoodSetpoint = this->HoodTable[closestPoint + 1];
        
            double FirstSetpointPower = fabs(CurrentDistance - this->distanceTable[closestPoint + 1]);
            double SecondSetpointPower = DistanceDelta;

            double CombinedSetpointSpeed = 
            ((SpeedSetPoint * FirstSetpointPower) + (DiffSpeedSetpoint * SecondSetpointPower)) / (FirstSetpointPower + SecondSetpointPower);
            
            double CombinedSetpointHood  = 
            ((HoodSetpoint * FirstSetpointPower) + (DiffHoodSetpoint * SecondSetpointPower)) / (FirstSetpointPower + SecondSetpointPower);
            

            HoodSetpoint = CombinedSetpointHood;
            SpeedSetPoint = CombinedSetpointSpeed;
            //std::cout << "Combined: " << CombinedSetpointSpeed / ( (FirstSetpointPower + SecondSetpointPower)) << std::endl;
        }
    }
    

    //std::cout << "closest point: " << closestPoint + 1 << " : " << DistanceDelta << " --> " << SpeedSetPoint << " : " << HoodSetpoint << std::endl;
    frc::SmartDashboard::PutBoolean("Target Detected", m_vision.IsDetectingTape());
    frc::SmartDashboard::PutBoolean("Shooter Ready", this->IsShooterAtSpeed(SpeedSetPoint));
    frc::SmartDashboard::PutBoolean("Hood Ready", this->IsHoodAtPos(HoodSetpoint));
    frc::SmartDashboard::PutNumber("Shooter Speed", this->GetShooterSpeed());
    frc::SmartDashboard::PutNumber("Speed Delta", this->GetShooterSpeed() - SpeedSetPoint);


    if (AutoSpinup){
        this->SetHoodToPos(HoodSetpoint);
        this->RunShooter(SpeedSetPoint);
    }
}

bool ShooterSubsystem::GetAutoSpinupState() {
    return this->AutoSpinup;
}

void ShooterSubsystem::ToggleAutoSpinup() {
    this->AutoSpinup = !this->AutoSpinup;
}

void ShooterSubsystem::RunShooter(double speed) {
    this->m_pid.SetSetpoint(speed / 4096);

    
    double RunningSpeed = this->m_pid.Calculate(this->GetShooterSpeed() / 4096);
    if (speed <= 0) RunningSpeed = 0;

    if (RunningSpeed < 0) RunningSpeed = 0;
    if (RunningSpeed > 0.8) RunningSpeed = 0.8;

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


    return ( fabs(this->GetShooterSpeed() - speed) <= 100 );

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
                this->SetHoodSpeed( (diff > 400) ? -1 : -0.3);
            }
            else {
                this->SetHoodSpeed((diff > 400) ? 1 : 0.3);
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
    if (pos == 0) {
        return this->IsLimitReached();
    }
    else {
        double diff = fabs(pos - this->GetHoodPos());

        return (diff < 50);
    }
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

bool ShooterSubsystem::ContainsShootingBall() {
    uint32_t sensorValue = m_sensor.GetProximity();

    double sensorFlipped = fabs(2047 - sensorValue);

    return sensorFlipped < 1730;
}