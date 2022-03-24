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

  void SetLeftLow(double speed);
  void SetRightLow(double speed);
  void SetLeftHigh(double speed);
  void SetRightHigh(double speed);

  int GetLowLeft();
  int GetLowRight();
  int GetHighLeft();
  int GetHighRight();

  void resetAll();

  void ResetLow();
  void ResetHigh();

  void ResetLowLeft();
  void ResetLowRight();
  void ResetHighLeft();
  void ResetHighRight();

  int GetMotorIdEncoder(int id);
  void ResetMotorId(int id);
  void SetMotorId(int id, double speed);


 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  WPI_TalonFX m_left_motor{1};
  WPI_TalonFX m_right_motor{11};
  WPI_TalonFX m_left_high_motor{3};
  WPI_TalonFX m_right_high_motor{5};

  double m_left_setpoint = 0;
  double m_right_setpoint = 0;
  double m_left_high_setpoint = 0;
  double m_right_high_setpoint = 0;

  
};
