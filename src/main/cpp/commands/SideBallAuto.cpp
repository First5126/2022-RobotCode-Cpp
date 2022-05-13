
#include "commands/SideBallAuto.h"

#include <frc2/command/ParallelCommandGroup.h>
#include <frc2/command/SequentialCommandGroup.h>

#include <commands/DriveDistanceCommand.h>
#include <commands/IntakeCommand.h>
#include <commands/ShooterCommand.h>
#include <frc2/command/InstantCommand.h>
#include <commands/TurnDegreesCommand.h>

#include <iostream>

SideBallAuto::SideBallAuto(DriveSubsystem* subsystem, IntakeSubsystem* intake, ShooterSubsystem* shooter)
    : m_drive{subsystem}
    , m_intake{intake}
    , m_shooter{shooter} {

    AddCommands(
        frc2::InstantCommand([this]() { this->intake_in = false; std::cout << "Intake OUT!" << std::endl; }),
        frc2::ParallelCommandGroup {  
            frc2::SequentialCommandGroup {
                DriveDistance(m_drive, []() {return 5;}),
                TurnDegrees(m_drive, [](){return -15;}),
                DriveDistance(m_drive, []() {return -(34 / 12); }),
                frc2::InstantCommand([this]() { this->intake_in = true; std::cout << "Intake IN!" << std::endl; })
            },
            IntakeCommand(m_intake, [this]() {return this->intake_in;})
        },
        frc2::SequentialCommandGroup {
            ShooterCommand(m_shooter, 
                [this]() {return this->m_shooter->GetAutoSpeedSetpoint(); },
                [this]() {return this->m_shooter->GetAutoHoodSetpoint(); }),
            frc2::InstantCommand([this]() { this->intake_in = false; })
        }
    );
}