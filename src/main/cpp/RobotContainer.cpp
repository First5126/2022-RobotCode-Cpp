// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include <iostream>
#include "frc2/command/RunCommand.h"
#include "commands/DefaultDriveCommand.h"
#include "commands/ShooterCommand.h"
#include "commands/HoodCommand.h"
#include "commands/TurnDegreesCommand.h"
#include "commands/IntakeCommand.h"

#include <frc2/command/ParallelCommandGroup.h>


bool isfinished() {
  return false;
}

std::vector<std::string> split(std::string text, char delim) {
    std::string line;
    std::vector<std::string> vec;
    std::stringstream ss(text);

    while(std::getline(ss, line, delim)) {
        vec.push_back(line);
    }

    return vec;

}

frc2::SequentialCommandGroup* RobotContainer::EasyAuto(std::string input) {
  std::vector<std::string> lines = split(input, '\n');

  frc2::SequentialCommandGroup* group = new frc2::SequentialCommandGroup{};

  for (auto i : lines) {
    std::vector<std::string> operations = split(i, ' ');

    if (operations.size() != 2) std::cout << "[ERROR]: Too many, or to little operations in file! Commands should look like `[CMD] (ARGS)`!" << std::endl << "Command looked like: " << i << std::endl;

    auto cmd = operations[0]; 
    auto opperand = std::stof(operations[1]);

    if (cmd == "Drive") group->AddCommands(DriveDistance(&m_drive, [this, opperand]() { return opperand; }));
    //else if (cmd == "Shoot") group->AddCommands(ShooterCommand(&m_shooter, [this, opperand]() { return opperand; }));
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
    [this]() { return -m_driverController.GetLeftY(); },
    [this]() { return m_driverController.GetRightX(); } 
  });


  m_compressor.EnableDigital();
  
  // Configure the button bindings
  ConfigureButtonBindings();
}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here
  
  // TODO: Rewrite for input from vision system.
  // This will allow us to automaticly determine 
  // the power that the shooter needs to run at
  // for us to get the ball into the goal!
  // 2850 5000
  frc2::JoystickButton(&m_driverController, 1)
  .WhenPressed ( 
    frc2::SequentialCommandGroup (
      frc2::ParallelCommandGroup {
        frc2::SequentialCommandGroup {
          DriveDistance{&m_drive, []() {return  5; }},
          DriveDistance{&m_drive, []() {return -5; }},
          frc2::InstantCommand([this]() { this->intake_in = true; })
        },
        IntakeCommand(&m_intake, [this]() {return this->intake_in; })
      },
      frc2::InstantCommand([this]() { this->intake_in = false; }),
      ShooterCommand(&m_shooter, []() {return 3000; }, []() {return 1000; })
    )
    
  ); // Example Speed FIXME!

  // This will run the intake when button is pressed
  frc2::JoystickButton(&m_driverController, 2)
  .WhenPressed ([this]() {m_intake.DeployIntake(); m_intake.RunIntake();    })
  .WhenReleased([this]() {m_intake.RetractIntake(); m_intake.StopAll();   });

  // Toggle the intake when button is pressed
  frc2::JoystickButton(&m_driverController, 4)
  .WhenPressed ([this]() { m_shooter.acuateServo(-1); })
  .WhenReleased([this]() { m_shooter.acuateServo(0.5); });



  //frc2::JoystickButton(&m_driverController, 3)
  //.WhenPressed ( this->EasyAuto(auto_code) );

  // 27in 2500 1000
  // 12in 2500 1500
  //  0in 2250 2000
  // 36in 2500  900
  // 48in 2500  850
  // 

  frc2::JoystickButton(&m_driverController, 3)
  .WhenPressed(
    new frc2::SequentialCommandGroup(
      ShooterCommand(&m_shooter, []() {return 2000;}, []() {return 2000;})
    )
  );

  frc2::JoystickButton(&m_driverController, 5)
  .WhenPressed(
    [this]() { m_compressor.Disable(); }
  );

  frc2::JoystickButton(&m_driverController, 6)
  .WhenPressed(
    [this]() { m_compressor.EnableDigital(); }
  );

  frc2::JoystickButton(&m_driverController, 7)
  .WhenPressed(
    new HoodCommand(&m_shooter, []() {return 0; })
  );

  frc2::JoystickButton(&m_driverController, 8)
  .WhenPressed(
    new HoodCommand(&m_shooter, []() {return 5010; })
  );
  
  frc2::JoystickButton(&m_driverController, 9)
  .WhenPressed ([this]() { m_intake.RunIntake(); })
  .WhenReleased([this]() { m_intake.StopAll(); });

  frc2::JoystickButton(&m_driverController, 10)
  .WhenPressed ([this]() { m_drive.ToggleShift(); });

}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return &m_autonomousCommand;
}

void RobotContainer::ResetAll() {
  std::cout << "RESET ALL" << std::endl;
}