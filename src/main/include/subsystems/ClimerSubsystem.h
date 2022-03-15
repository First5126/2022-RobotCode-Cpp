#pragma once

#include <frc2/command/SubsystemBase.h>

#include "ctre/Phoenix.h"

class ClimerSubsystem : public frc2::SubsystemBase {
 public:
  ClimerSubsystem();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  void Set(double speed);


 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  WPI_TalonFX m_left_motor{5};
  WPI_TalonFX m_right_motor{11};
};
