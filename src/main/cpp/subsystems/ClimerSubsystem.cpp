#include "subsystems/ClimerSubsystem.h"


ClimerSubsystem::ClimerSubsystem() {
  // Implementation of subsystem constructor goes here.

  this->m_left_motor.Set(0);
  this->m_right_motor.Set(0);

  m_left_high_motor = new rev::CANSparkMax{18, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  m_right_high_motor = new rev::CANSparkMax{19, rev::CANSparkMaxLowLevel::MotorType::kBrushless};

}

void ClimerSubsystem::Periodic() {
  // Implementation of subsystem periodic method goes here.
}

void ClimerSubsystem::SetLow(double speed) {
    this->m_left_motor.Set(speed);
    this->m_right_motor.Set(-speed);
}

void ClimerSubsystem::SetHigh(double speed) {
    this->m_right_high_motor->Set(speed);
    this->m_left_high_motor->Set(-speed);
}
