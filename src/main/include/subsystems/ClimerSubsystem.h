#pragma once

#include <frc2/command/SubsystemBase.h>
#include "rev/CANSparkMax.h"

#include "ctre/Phoenix.h"

class ClimerSubsystem : public frc2::SubsystemBase {
 public:
  ClimerSubsystem();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  void SetLow(double speed);
  void SetHigh(double speed);


 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  WPI_TalonFX m_left_motor{5};
  WPI_TalonFX m_right_motor{11};

  rev::CANSparkMax* m_left_high_motor;
  rev::CANSparkMax* m_right_high_motor;

  
};
