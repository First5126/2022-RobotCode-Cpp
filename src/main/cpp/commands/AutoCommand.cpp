
#include "commands/AutoCommand.h"

#include <frc2/command/ParallelCommandGroup.h>
#include <frc2/command/SequentialCommandGroup.h>

#include <commands/DriveDistanceCommand.h>
#include <commands/IntakeCommand.h>
#include <commands/ShooterCommand.h>
#include <frc2/command/InstantCommand.h>

#include <commands/SideBallAuto.h>

#include <iostream>

AutoCommand::AutoCommand(DriveSubsystem* subsystem, IntakeSubsystem* intake, ShooterSubsystem* shooter)
    : m_drive{subsystem}
    , m_intake{intake}
    , m_shooter{shooter} {

    AddCommands(
        frc2::ParallelCommandGroup {
          frc2::SequentialCommandGroup {
            DriveDistance{m_drive, []() {return  5; }},
            DriveDistance{m_drive, []() {return -3; }},
            frc2::InstantCommand([this]() { this->intake_in = true; })
          },
          IntakeCommand(m_intake, [this]() {return this->intake_in; })
      },
      //ShooterCommand(m_shooter, []() {return 2250; }, []() {return 850; }),
      frc2::SequentialCommandGroup {
        ShooterCommand(m_shooter,
              [this]() {return m_shooter->GetAutoSpeedSetpoint(); },
              [this]() {return m_shooter->GetAutoHoodSetpoint(); }),

          frc2::InstantCommand([this]() { this->intake_in = false; }),
          DriveDistance{m_drive, []() {return 5; }}
          //IntakeCommand(m_intake, [this]() {return this->intake_in; }),   
      }  

      //SideBallAuto(m_drive, m_intake, m_shooter)
    );
}