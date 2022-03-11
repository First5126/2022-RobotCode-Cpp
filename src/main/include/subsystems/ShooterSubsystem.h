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

#pragma once

#include <frc2/command/SubsystemBase.h>

#include "ctre/Phoenix.h"
#include "rev/ColorSensorV3.h"
#include "rev/CANSparkMax.h"
#include <wpi/numbers>
#include <frc/controller/PIDController.h>
#include <frc/DigitalInput.h>
#include "rev/RelativeEncoder.h"
#include <frc/Encoder.h>


class ShooterSubsystem : public frc2::SubsystemBase {
 public:
  ShooterSubsystem();
  ~ShooterSubsystem();

  // Runs about every called packet
  void Periodic() override;


  // Start to spin the shooter to a speed [-!, !]
  // Sets the vel of the shooter in (encoder / second)
  void RunShooter(double speed);

  // Ask the shooter if its at the speed that we set it too
  bool IsShooterAtSpeed(double speed);

  // Get the speed in (encoder / second) that the shooter is at
  double GetShooterSpeed();
  
  // Feed the balls into the shooter for shooting
  void FeedBall();

  // Stop feeding the balls
  void StopFeedBall();

  // STOP ALL MOTORS FROM SPINING
  void StopAll();

  bool ContainsBall();

  bool IsCurrectColor();

  bool IsLimitReached();
  void resetHood();
  
  void SetHoodSpeed(double speed);

  // Set the hood to pos
  void SetHoodToPos(int pos);

  bool HasShooterBeenReset();

  bool IsHoodAtPos(int pos);

  int GetHoodPos();
  

 private:
  rev::CANSparkMax *ShooterLeft;
  rev::CANSparkMax *ShooterRight;

  rev::CANSparkMax *Hood;

  WPI_TalonSRX FeederMotor {15};

  double Shooter_Kp = 0.25;
  double Shooter_Ki = 0;
  double Shooter_Kd = 0;

  frc::PIDController m_pid {0.0100, 0.0000, 0.000000};

  double shooter_speed = 0;

  rev::SparkMaxRelativeEncoder *m_shooter_encoder;
  //rev::SparkMaxAlternateEncoder *m_hood_encoder;

  frc::Encoder hood_encoder {5, 6};


  rev::ColorSensorV3 m_sensor {frc::I2C::Port::kOnboard} ;

  frc::DigitalInput hood_limit {9};

  bool ShooterReset = false;
};
