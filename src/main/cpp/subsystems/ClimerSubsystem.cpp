#include "subsystems/ClimerSubsystem.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <iostream>

ClimerSubsystem::ClimerSubsystem()
{
  // Implementation of subsystem constructor goes here.

  this->m_left_motor.Set(0);
  this->m_right_motor.Set(0);
  this->m_left_high_motor.Set(0);
  this->m_right_high_motor.Set(0);

}

void ClimerSubsystem::Periodic() {
  // Implementation of subsystem periodic method goes here.
  frc::SmartDashboard::PutNumber("Left Low", GetLowLeft());
  frc::SmartDashboard::PutNumber("Right Low", GetLowRight());
  frc::SmartDashboard::PutNumber("Left High", GetHighLeft());
  frc::SmartDashboard::PutNumber("Right High", GetHighRight());
  
}

void ClimerSubsystem::SetLow(double speed) {
    this->SetLeftLow(speed);
    this->SetRightLow(speed);
}

void ClimerSubsystem::SetHigh(double speed) {
    this->SetLeftHigh(speed);
    this->SetRightHigh(speed);
}


int ClimerSubsystem::GetLowLeft() {
    return m_left_motor.GetSelectedSensorPosition(1) - m_left_setpoint;
}
int ClimerSubsystem::GetLowRight() {
    return (-m_right_motor.GetSelectedSensorPosition(1)) - m_right_setpoint;
}
int ClimerSubsystem::GetHighLeft() {
    return (-m_left_high_motor.GetSelectedSensorPosition(1)) - m_left_high_setpoint;
}
int ClimerSubsystem::GetHighRight() {
    return (m_right_high_motor.GetSelectedSensorPosition(1)) - m_right_high_setpoint;
}
void ClimerSubsystem::resetAll() {
    ResetHigh();
    ResetLow();
}
void ClimerSubsystem::ResetLow() {
    ResetLowLeft();
    ResetLowRight();
}
void ClimerSubsystem::ResetHigh() {
    ResetHighLeft();
    ResetHighRight();
}
void ClimerSubsystem::ResetLowLeft() {
    m_left_setpoint = m_left_motor.GetSelectedSensorPosition(1);
}
void ClimerSubsystem::ResetLowRight() {
    m_right_setpoint = (-m_right_motor.GetSelectedSensorPosition(1)) ;
}
void ClimerSubsystem::ResetHighLeft() {
    m_left_high_setpoint = -m_left_high_motor.GetSelectedSensorPosition(1);
}
void ClimerSubsystem::ResetHighRight() {
    m_right_high_setpoint = m_right_high_motor.GetSelectedSensorPosition(1);
}

void ClimerSubsystem::SetLeftLow(double speed) {
    std::cout << "left: " << speed << std::endl;
    m_left_motor.Set(speed);
}

void ClimerSubsystem::SetRightLow(double speed) {
    m_right_motor.Set(-speed);
}
void ClimerSubsystem::SetLeftHigh(double speed) {
    m_left_high_motor.Set(speed);
}
void ClimerSubsystem::SetRightHigh(double speed) {
    m_right_high_motor.Set(-speed);
}

int ClimerSubsystem::GetMotorIdEncoder(int id) {
    switch (id)
    {
        case 0:
            return this->GetLowLeft();
            
        case 1:
            return this->GetLowRight();

        case 2:
            return this->GetHighLeft();

        case 3:
            return this->GetHighRight();

        default:
            std::cout << "MOTOR NOT FOUND!" << std::endl;
            return 0;
            break;
        }
}

void ClimerSubsystem::ResetMotorId(int id) {
    switch (id)
    {
        case 0:
            this->ResetLowLeft();
            break;

        case 1:
            this->ResetLowRight();
            break;

        case 2:
            this->ResetHighLeft();
            break;

        case 3:
            this->ResetHighRight();
            break;

        default:
            std::cout << "MOTOR NOT FOUND!" << std::endl;
            break;
    }
}

void ClimerSubsystem::SetMotorId(int id, double speed) {
    switch (id)
    {
        case 0:
            this->SetLeftLow(speed);
            break;

        case 1:
            this->SetRightLow(speed);
            break;

        case 2:
            this->SetLeftHigh(speed);
            break;

        case 3:
            this->SetRightHigh(speed);
            break;

        default:
            std::cout << "MOTOR NOT FOUND!" << std::endl;
            break;
    }
}