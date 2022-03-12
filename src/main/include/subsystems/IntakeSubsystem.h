/*
* TEAM 5126 (c) : 2022 FRC Rapid React
* Command Based C++ Robot Code 
* 
* [Intake]
* 
*       |\
* [=====] *
* 
* ## What does this subsystem do?
* This subsystem can extend or retract the intake.
* It can also run the intake, or stop it.
*/ 
#pragma once

#include <frc2/command/SubsystemBase.h>

#include "ctre/Phoenix.h"
#include "rev/ColorSensorV3.h"
#include "rev/CANSparkMax.h"
#include <wpi/numbers>
#include <frc/controller/PIDController.h>
#include <frc/Compressor.h>
#include <frc/Solenoid.h>
#include <frc/DoubleSolenoid.h>
#include <frc/DigitalInput.h>

class IntakeSubsystem : public frc2::SubsystemBase {
 public:
  IntakeSubsystem();

  // Runs every packet
  void Periodic() override;

  // Extend the intake out of the robot
  void DeployIntake();

  // Take the intake back into the robot
  void RetractIntake();

  // Toggle the state of intake
  // call DeployIntake() if the intake is inside the robot
  // call RetractIntake() if the intake is outside the robot
  void ToggleIntake();

  // This will cause the wheels on the intake to spin
  void RunIntake();

  // Stop all the wheels from moving
  void StopIntake();

  // Stop the motor and stop the Intake from moving
  void StopAll();

  bool GetIntakeState();


 private:
 rev::CANSparkMax* IntakeMotor;

 bool IntakeState = false;
 
 frc::DoubleSolenoid m_arm {30, frc::PneumaticsModuleType::REVPH, 0, 1}; 

 frc::DigitalInput intake_in {8};
};