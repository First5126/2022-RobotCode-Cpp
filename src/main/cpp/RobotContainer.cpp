// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include <iostream>
#include "frc2/command/RunCommand.h"
#include "commands/DefaultDriveCommand.h"

RobotContainer::RobotContainer() 
  : m_autonomousCommand(&m_subsystem)
    {
  // Initialize all of your commands and subsystems here

  m_drive.SetDefaultCommand( DefaultDrive {
    &m_drive,
    [this]() { return m_driverController.GetLeftY(); },
    [this]() { return m_driverController.GetRightX(); } 
  });

  // Configure the button bindings
  ConfigureButtonBindings();
}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here
  
  // TODO: Rewrite for input from vision system.
  // This will allow us to automaticly determine 
  // the power that the shooter needs to run at
  // for us to get the ball into the goal!
  frc2::JoystickButton(&m_driverController, 6)
  .WhenPressed ([this]() {m_shooter.RunShooter(10000); }) // Example Speed FIXME!
  .WhenReleased([this]() {m_shooter.StopAll();         });
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return &m_autonomousCommand;
}

void RobotContainer::ResetAll() {
  std::cout << "RESET ALL" << std::endl;
}