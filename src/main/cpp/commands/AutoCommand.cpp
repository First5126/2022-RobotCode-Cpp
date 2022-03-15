
#include "commands/AutoCommand.h"

#include <frc2/command/ParallelCommandGroup.h>
#include <frc2/command/SequentialCommandGroup.h>

#include <commands/DriveDistanceCommand.h>
#include <commands/IntakeCommand.h>
#include <commands/ShooterCommand.h>
#include <frc2/command/InstantCommand.h>

AutoCommand::AutoCommand(DriveSubsystem* subsystem, IntakeSubsystem* intake, ShooterSubsystem* shooter)
    : m_drive{subsystem}
    , m_intake{intake}
    , m_shooter{shooter} {

    AddCommands(
        frc2::ParallelCommandGroup {
        frc2::SequentialCommandGroup {
          DriveDistance{m_drive, []() {return  5; }},
          DriveDistance{m_drive, []() {return -5; }},
          frc2::InstantCommand([this]() { this->intake_in = true; })
        },
        IntakeCommand(m_intake, [this]() {return this->intake_in; })
      },
      frc2::InstantCommand([this]() { this->intake_in = false; }),
      ShooterCommand(m_shooter, []() {return 2250; }, []() {return 850; })
    );
}