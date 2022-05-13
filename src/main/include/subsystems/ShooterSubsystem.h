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
#include <frc/Servo.h>

#include "subsystems/VisionSubsystem.h"

#include <frc/SerialPort.h>



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

  void acuateServo(double angle);

  bool ContainsShootingBall();
  
  void ToggleAutoSpinup();

  bool GetAutoSpinupState();

  double GetRobotAngleOffset();

  int GetAutoHoodSetpoint();
  int GetAutoSpeedSetpoint();

  bool IsConnected();

  inline void CancelCommand() { m_commandState = false;}
  inline void EnableCommand() { m_commandState = true; }

  inline bool GetCommandState() { return !m_commandState; }

 private:
  bool m_commandState = true;

  rev::CANSparkMax *ShooterLeft;
  rev::CANSparkMax *ShooterRight;

  rev::CANSparkMax *Hood;

  WPI_TalonSRX FeederMotor {15};

  double Shooter_Kp = 0.25;
  double Shooter_Ki = 0;
  double Shooter_Kd = 0;

  // ku = 5, time = .44
  double Ku = 3;
  double time = 0.44;

  frc::PIDController m_pid {0.6 * Ku, 1.2 * Ku / time, 3 * Ku * time / 40};

  double shooter_speed = 0;

  rev::SparkMaxRelativeEncoder *m_shooter_encoder;
  //rev::SparkMaxAlternateEncoder *m_hood_encoder;

  frc::Encoder hood_encoder {5, 6};

  VisionSubsystem m_vision;


  rev::ColorSensorV3 m_sensor {frc::I2C::Port::kOnboard} ;

  frc::DigitalInput hopperball {7};
  frc::DigitalInput hood_limit {9};

  bool ShooterReset = false;

  frc::Servo m_wipe {0};

  const static int TABLESIZE = 9;

  int HoodSetpoint = 0;
  int SpeedSetPoint = 0;

  int distanceTable[TABLESIZE] = {
    0,
    24,
    27,
    35,
    47,
    57,
    68,
    72,
    84
  };

  int SpeedTable[TABLESIZE] = {
    3200 + 25, //0
    3100 + 10, //24
    3100 + 25, //27 
    3175 + 50, //36
    3200 + 25, //48
    3175 + 90, //60
    3350 + 50, //68 --
    3350 + 25, //72
    3450 + 25  //84
  };

  int HoodTable[TABLESIZE] = {
    1875,      //0
    1400,      //24
    1200 + 25, //27
    1100,      //36
    1025,      //48
    1000 - 10, //60
    940,       //68 --
    975,       //72
    975        //84
  };

  bool AutoSpinup = false;

  // 0  - BACK | 3200, 1875
  // 12 - BACK | 3100, 1500
  // 24 - BACK | 3100, 1200
  // 36 - BACK | 3175, 1100
  // 48 - BACK | 3175, 1025
  // 60 - BACK | 3175, 1000
  // 72 - BACK | 3350,  975
  // 84 - BACK | 3450,  975

  //  0in 2250 2000 BACK  SIDE
  // 12in 2500 1500 BACK  SIDE
  // 27in 2500 1000 BACK  SIDE
  // 36in 2500  900 BACK  SIDE
  // 48in 2500  850 BACK  SIDE
  // 60in 2525  800 BACK  SIDE
  // 72in 2475  750 BACK  SIDE
  // 84in 2550  700 BACK  SIDE

  //  0in 2500 3000 FRONT SIDE
  // 12in 2500 3200 FRONT SIDE
  // 24in 2550 3400 FRONT SIDE
  // 36in 2550 3600 FRONT SIDE
  // 48in 2575 3800 FRONT SIDE
  // 60in 2600 4000 FRONT SIDE
  // FAR  3200 5400 FRONT SIDE // DANGER ANGLE
  // 72in 2600 4200 FRONT SIDE
  // 84in 2600 4400 FRONT SIDE
  // 96in 2675 4600 FRONT SIDE

  

};
