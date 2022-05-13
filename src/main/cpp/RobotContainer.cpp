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
#include "commands/TargetAlign.h"

#include "frc/smartdashboard/SmartDashboard.h"
#include <frc2/command/ParallelCommandGroup.h>
#include "commands/ClimerCommand.h"

#include "commands/ClimerSet.h"
#include "commands/ClimerHome.h"

#include <frc/SerialPort.h>

bool isfinished() {
  return false;
}

RobotContainer::RobotContainer() 
  : m_autonomousCommand(&m_drive, &m_intake, &m_shooter)
    {

  frc::CameraServer::StartAutomaticCapture();
  // Initialize all of your commands and subsystems here


  m_drive.SetDefaultCommand( DefaultDrive {
    &m_drive,
    [this]() { return -m_drive_controller.GetLeftY(); },
    [this]() { return m_drive_controller.GetRightX(); } 
  });

  m_climer.SetDefaultCommand( ClimerCommand {
    &m_climer,
    [this]() { return m_buttons_controller.GetRawAxis(3); },
    [this]() { return m_buttons_controller.GetRawAxis(2); },
    [this]() { return m_drive_controller.GetRawAxis(3); },
    [this]() { return m_drive_controller.GetRawAxis(2); }
  });


  // ------------------------------ COMPRESSOR ----------------------- // 
  //m_compressor.EnableDigital();
  m_compressor.EnableHybrid(units::pounds_per_square_inch_t(90), units::pounds_per_square_inch_t(120));
  //m_compressor.EnableAnalog(units::pounds_per_square_inch_t(90), units::pounds_per_square_inch_t(120));
  
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
  
  /*frc2::JoystickButton(&m_driverController, 1)
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
      ShooterCommand(&m_shooter, []() {return 2425; }, []() {return 850; })
    )
  ); // Example Speed FIXME!
  */

  // This will run the intake when button is pressed
  


  //frc2::JoystickButton(&m_driverController, 3)
  //.WhenPressed ( this->EasyAuto(auto_code) );

  // 27in 2500 1000 BACK  SIDE
  // 12in 2500 1500 BACK  SIDE
  //  0in 2250 2000 BACK  SIDE
  // 36in 2500  900 BACK  SIDE
  // 48in 2500  850 BACK  SIDE
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
  // 60in 2525  800 BACK  SIDE
  // 72in 2475  750 BACK SIDE
  // 84in 2550  700 BACK SIDE
  // 96in 

  frc2::JoystickButton(&m_buttons_controller, 2) // B
  .WhenPressed ([this]() {m_intake.DeployIntake(); m_intake.RunIntake();    })
  .WhenReleased([this]() {m_intake.RetractIntake(); m_intake.StopAll();   });

  // Toggle the intake when button is pressed
  /*frc2::JoystickButton(&m_driverController, 3) // X
  .WhenPressed ([this]() { m_climer.Set(0.8); })
  .WhenReleased([this]() { m_climer.Set(0); });

  frc2::JoystickButton(&m_driverController, 4) // Y
  .WhenPressed ([this]() { m_climer.Set(-1); })
  .WhenReleased([this]() { m_climer.Set(0); });*/


  /* SHOOTER CLOSE
  frc2::JoystickButton(&m_buttons_controller, 3) // X
  .WhenPressed( new ShooterCommand(&m_shooter, []() {return 2300; }, []() {return 1900;}));
  */ 

  frc2::JoystickButton(&m_buttons_controller, 3) // X
  .WhenPressed( 
    //new ShooterCommand(&m_shooter, []() {return 2400; }, []() {return 3100;})
    //new ShooterCommand(&m_shooter, []() {return 2000; }, []() {return 1550; })
    new ShooterCommand(&m_shooter, []() {return 3450; }, []() {return 3325; })
    );

    


  frc2::JoystickButton(&m_buttons_controller, 4) // Y
  .WhenPressed(
    new ShooterCommand(&m_shooter,
      [this]() { return 1850; },
      [this]() { return 4750; }
    )
  );

  /*frc2::JoystickButton(&m_buttons_controller, 10)
  .WhenPressed( new ShooterCommand(&m_shooter,
  [this]() { return 3200; },
  [this]() { return 5400; }
  ));*/
  frc2::JoystickButton(&m_buttons_controller, 10) // Left Joystick
  .WhenPressed(
    new ClimerSet(&m_climer, []() {return 1.0;}, []() {return 1.0;})
  );

  frc2::JoystickButton(&m_drive_controller, 1) // A - drive controller
  .WhenPressed(
    [this]() {m_climer.resetAll(); }
  );

  frc2::JoystickButton(&m_drive_controller, 8) // start
  .WhenPressed(
    new ClimerSet(&m_climer, []() {return 1.0;}, []() {return 1.0;})
  );

  frc2::JoystickButton(&m_drive_controller, 7) // func
  .WhenPressed(
    new ClimerSet(&m_climer, []() {return -0.9;}, []() {return -0.9;})
  );


  frc2::JoystickButton(&m_drive_controller, 3) // X - drive controller
  .WhenPressed(
    [this] () { m_shooter.CancelCommand(); }
  ).WhenReleased(
    [this]() { m_shooter.EnableCommand(); }
  );

  frc2::JoystickButton(&m_drive_controller, 2) // B - drive controller
  .WhenPressed(
    new TargetAlign(&m_shooter, &m_drive)
  );

  frc2::JoystickButton(&m_drive_controller, 4)  // Y - drive controller
  .WhenPressed(
    [this]() {m_shooter.ToggleAutoSpinup(); }
  );

  // ====================== HIGH
  // 0  - BACK | 3200, 1875
  // 12 - BACK | 3100, 1500
  // 24 - BACK | 3100, 1200
  // 36 - BACK | 3175, 1100
  // 48 - BACK | 3175, 1025
  // 60 - BACK | 3175, 1000
  // 72 - BACK | 3350,  975
  // 84 - BACK | 3450,  975

  // ====================== LOW
  // 0  - BACK | 2050, 1550
  // 12 - BACK | 3100, 1500
  // 24 - BACK | 3100, 1200
  // 36 - BACK | 3175, 1100
  // 48 - BACK | 3175, 1025
  // 60 - BACK | 3175, 1000
  // 72 - BACK | 3350,  975
  // 84 - BACK | 3450,  975



  /*frc2::JoystickButton(&m_buttons_controller, 1) // A
  .WhenPressed(
    new frc2::SequentialCommandGroup(
      ShooterCommand(&m_shooter, []() {return 2050;}, []() {return 1600;})
      //ShooterCommand(&m_shooter, []() {return 3700;}, []() {return 5000;})
    )
  );*/
  frc2::JoystickButton(&m_buttons_controller, 1) // A
  .WhenPressed( new ShooterCommand(&m_shooter,
  [this]() {return m_shooter.GetAutoSpeedSetpoint(); },
  [this]() {return m_shooter.GetAutoHoodSetpoint();}));

  frc2::JoystickButton(&m_buttons_controller, 5) // left bumper
  .WhenPressed(
    [this]() { m_compressor.Disable(); }
  );

  frc2::JoystickButton(&m_buttons_controller, 6) // right bumper
  .WhenPressed(
    [this]() { m_compressor.EnableDigital(); }
  );

  frc2::JoystickButton(&m_buttons_controller, 7) // back
  .WhenPressed(
    new HoodCommand(&m_shooter, []() {return 0; })
  );

  frc2::JoystickButton(&m_buttons_controller, 8) // start
  .WhenPressed(
    new HoodCommand(&m_shooter, []() {return 5010; })
  );
  
  frc2::JoystickButton(&m_buttons_controller, 9) // left joystick 
  .WhenPressed ([this]() { m_intake.RunIntake(); })
  .WhenReleased([this]() { m_intake.StopAll(); });

  frc2::JoystickButton(&m_drive_controller, 5) // left bumper - drive controller
  .WhenPressed ([this]() { m_drive.SetShift(1); });

  frc2::JoystickButton(&m_drive_controller, 6) // right bumper - drive controller 
  .WhenPressed ([this]() { m_drive.SetShift(0); });

}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return &m_autonomousCommand;
}

void RobotContainer::ResetAll() {
  std::cout << "RESET ALL" << std::endl;
}