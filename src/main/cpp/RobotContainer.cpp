// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include <iostream>
#include "frc2/command/RunCommand.h"
#include "commands/DefaultDriveCommand.h"
#include "commands/ShooterCommand.h"

std::vector<std::string> split(std::string text, char delim) {
    std::string line;
    std::vector<std::string> vec;
    std::stringstream ss(text);

    while(std::getline(ss, line, delim)) {
        vec.push_back(line);
    }

    return vec;
}

frc2::SequentialCommandGroup RobotContainer::EasyAuto(std::string input) {
  std::vector<std::string> lines = split(input, '\n');

  frc2::SequentialCommandGroup group {};

  for (auto i : lines) {
    std::vector<std::string> operations = split(i, ' ');

    if (operations.size() != 2) std::cout << "[ERROR]: Too many, or to little operations in file! Commands should look like `[CMD] (ARGS)`!" << std::endl;

    auto cmd = operations[0]; 
    auto opperand = std::stof(operations[1]);

    if (cmd == "Drive") group.AddCommands(DriveDistance(&m_drive, [this, opperand]() { return opperand; }));
    else if (cmd == "Shoot") group.AddCommands(ShooterCommand(&m_shooter, [this, opperand]() { return opperand; }));
    else if (cmd == "Turn") ;
    else std::cout << "[ERROR]: \'" << cmd << "\' IS NOT FOUND!" << std::endl;
  }

  return group;
}

RobotContainer::RobotContainer() 
  : m_autonomousCommand(&m_drive)
    {
  // Initialize all of your commands and subsystems here


  m_drive.SetDefaultCommand( DefaultDrive {
    &m_drive,
    [this]() { return m_driverController.GetRightX(); },
    [this]() { return -m_driverController.GetLeftY(); } 
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
  frc2::JoystickButton(&m_driverController, 1)
  .WhenPressed ( new ShooterCommand{&m_shooter, [this]() {return 2850;} } ); // Example Speed FIXME!

  // This will run the intake when button is pressed
  frc2::JoystickButton(&m_driverController, 2)
  .WhenPressed ([this]() {m_shooter.FeedBall();    })
  .WhenReleased([this]() {m_shooter.StopFeedBall();   });

  // Toggle the intake when button is pressed
  frc2::JoystickButton(&m_driverController, 4)
  .WhenPressed ([this]() {m_intake.ToggleIntake(); });

  std::string auto_code = R"(
    Drive 10
    Shoot 2850
    Drive -10
    Turn 0
  )";


  /*frc2::JoystickButton(&m_driverController, 3)
  .WhenPressed ( this->EasyAuto(auto_code) );*/

  frc2::JoystickButton(&m_driverController, 3)
  .WhenPressed(
    new frc2::SequentialCommandGroup(
      ShooterCommand(&m_shooter, []() {return 1000;})
    )
  );

  

  frc2::JoystickButton(&m_driverController, 9)
  .WhenPressed ([this]() {m_drive.ArcadeDrive(0,0);});

}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return &m_autonomousCommand;
}

void RobotContainer::ResetAll() {
  std::cout << "RESET ALL" << std::endl;
}