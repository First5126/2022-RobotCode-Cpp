#pragma once

#include <frc2/command/SubsystemBase.h>

#include "ctre/Phoenix.h"
#include "rev/ColorSensorV3.h"
#include "rev/CANSparkMax.h"

#include "frc/motorcontrol/MotorControllerGroup.h"
#include "frc/drive/DifferentialDrive.h"
#include "frc/kinematics/DifferentialDriveOdometry.h"

#include <units/acceleration.h>
#include <units/angle.h>
#include <units/length.h>
#include <units/time.h>
#include <units/velocity.h>
#include <units/voltage.h>
#include <wpi/numbers>


class DriveSubsystem : public frc2::SubsystemBase {
 public:
  DriveSubsystem();

  
  void Periodic() override;

  void ArcadeDrive(double fwd, double rot);
  void TankDriveVolts(units::volt_t left, units::volt_t right);

  void ResetEncoders();
  double GetAverageEncoderDistance();

  double GetLeftEncoderPos();
  double GetRightEncoderPos();

  void SetMaxSpeed(double speed);
  units::degree_t GetHeading() const;

  double GetTurnRate();
  frc::Pose2d GetPose();

  frc::DifferentialDriveWheelSpeeds GetWheelSpeeds();
  void ResetOdometry(frc::Pose2d pose);


 private:
  WPI_TalonFX LFMotor {2};
  WPI_TalonFX LBMotor {4};

  WPI_TalonFX RFMotor {8};
  WPI_TalonFX RBMotor {6};

  frc::MotorControllerGroup m_left  {LFMotor, LBMotor};
  frc::MotorControllerGroup m_right {RFMotor, RBMotor};

  frc::DifferentialDrive m_drive {m_left, m_right};

  double ZeroEncoderPos_Left = 0;
  double ZeroEncoderPos_right = 0;

  frc::DifferentialDriveOdometry m_tacker { frc::Rotation2d() };

  double MaxDriveSpeed = 0;
  
  
};
