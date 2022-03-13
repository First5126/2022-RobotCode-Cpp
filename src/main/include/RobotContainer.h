// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/Command.h>

#include "commands/ExampleCommand.h"
#include "subsystems/ExampleSubsystem.h"
#include "subsystems/DriveSubsystem.h"
#include "subsystems/ShooterSubsystem.h"
#include "subsystems/IntakeSubsystem.h"
#include "commands/DriveDistanceCommand.h"

#include "frc/XboxController.h"
#include <frc/controller/PIDController.h>
#include <frc/controller/RamseteController.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/trajectory/Trajectory.h>
#include <frc/trajectory/TrajectoryGenerator.h>
#include <frc/trajectory/constraint/DifferentialDriveVoltageConstraint.h>
#include <frc2/command/InstantCommand.h>
#include <frc2/command/RamseteCommand.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/button/JoystickButton.h>
#include <frc/Compressor.h>
#include "commands/AutoCommand.h"

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and button mappings) should be declared here.
 */
class RobotContainer {
 public:
  RobotContainer();

  frc2::Command* GetAutonomousCommand();

  void ResetAll();

  frc::Compressor m_compressor{30, frc::PneumaticsModuleType::REVPH};

 public:

  bool intake_in = false;

  // The robot's subsystems and commands are defined here...
  ExampleSubsystem m_subsystem;
  AutoCommand m_autonomousCommand;

  frc::XboxController m_driverController { 1 };
  frc::XboxController m_drive_controller { 0 };


  DriveSubsystem m_drive;
  ShooterSubsystem m_shooter;
  IntakeSubsystem m_intake;


  frc2::SequentialCommandGroup* EasyAuto(std::string input);

  void ConfigureButtonBindings();

  
};
