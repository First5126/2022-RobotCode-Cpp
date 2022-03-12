/*
* TEAM 5126 (c) : 2022 FRC Rapid React
* Command Based C++ Robot Code 
* 
* [Drive Train]
* 
*      |O   |\
* ... [=====] *
* 
* ## What does this subsystem do?
* This subsystem can drive the wheels of the robot.
* It can also get the position of the robot in 2d space!
*/ 

#pragma once

#include <frc2/command/SubsystemBase.h>

#include "ctre/Phoenix.h"
#include "rev/ColorSensorV3.h"
#include "rev/CANSparkMax.h"

#include "frc/motorcontrol/MotorControllerGroup.h"
#include "frc/drive/DifferentialDrive.h"
#include "frc/kinematics/DifferentialDriveOdometry.h"
#include "frc/ADXRS450_Gyro.h"

#include <units/acceleration.h>
#include <units/angle.h>
#include <units/length.h>
#include <units/time.h>
#include <units/velocity.h>
#include <units/voltage.h>
#include <wpi/numbers>


#include "frc/controller/PIDController.h"

#include <frc/Solenoid.h>

class DriveSubsystem : public frc2::SubsystemBase {
 public:
  DriveSubsystem();
  ~DriveSubsystem();

  // Runs ever activation packet
  void Periodic() override;
  
  /*
  * |O----O| Robot:
  * |      |   This method Drives the robot with
  * |      |     values between [-1, 1] for forward and rotation.
  * |O----O|
  */
  void ArcadeDrive(double fwd, double rot);

  // Drives the robot with voltage instead of %
  void TankDriveVolts(units::volt_t left, units::volt_t right);

  // Reset the encoders on the drive motors
  void ResetEncoders();

  // tank drive
  void TankDrive(double left, double right);

  // Get the distance that the robot has travled from both motors
  double GetAverageEncoderDistance();

  // Get the left encoder value
  double GetLeftEncoderPos();

  // Get the right encoder value
  double GetRightEncoderPos();

  // Set the max speed that the robot can travel 
  void SetMaxSpeed(double speed);

  // Drive Certen amount of feet
  double CalcualteDriveEncoder(double ft);

  // Get the degree that the robot is facing [-180, 180]
  double GetHeading();

  // Get the rate at which the robot is turning
  double GetTurnRate();

  // Get the position in 2d where the robot is
  frc::Pose2d GetPose();

  double SetLeftSpeed(double speed);
  double SetRightSpeed(double speed);

  void resetHeading();


  bool CheckMotors();

  void ToggleShift();


  // Get the wheel speeds
  //frc::DifferentialDriveWheelSpeeds GetWheelSpeeds();

  // Reset the the robot in 2d space
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

  double EncoderPerRPM = 2048;
  double GearBoxValue = 15.00;
  double WheelRPM_to_Distance_in_feet = 4.00 / (2 * (M_PI)); // 4 / 2(pi)

  double EncoderSetLeftValue = 0;
  double EncoderSetRightValue = 0;

  double EncoderStartLeftValue = 0;
  double EncoderStartRightValue = 0;

  frc::ADXRS450_Gyro gyro;
  
  double Kp = 3.4933;
  double Ki = 0;
  double Kd = 0.066062;

  frc::PIDController pid_left {Kp, Ki, Kd};
  frc::PIDController pid_right {Kp, Ki, Kd};

  bool ShiftedState = false;
  
  frc::Solenoid right_piston {30, frc::PneumaticsModuleType::REVPH, 2};
  frc::Solenoid left_piston {30, frc::PneumaticsModuleType::REVPH, 3};
  
};
