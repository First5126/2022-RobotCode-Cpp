#include "subsystems/ClimerSubsystem.h"


ClimerSubsystem::ClimerSubsystem() {
  // Implementation of subsystem constructor goes here.

  this->m_left_motor.Set(0);
  this->m_right_motor.Set(0);

}

void ClimerSubsystem::Periodic() {
  // Implementation of subsystem periodic method goes here.
}

void ClimerSubsystem::Set(double speed) {
    this->m_left_motor.Set(speed);
    this->m_right_motor.Set(-speed);
}
