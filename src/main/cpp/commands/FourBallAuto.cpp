
#include "commands/FourBallAuto.h"

#include <frc2/command/ParallelCommandGroup.h>
#include <frc2/command/SequentialCommandGroup.h>

#include <commands/DriveDistanceCommand.h>
#include <commands/IntakeCommand.h>
#include <commands/ShooterCommand.h>
#include <commands/TurnDegreesCommand.h>
#include <frc2/command/InstantCommand.h>

#include <iostream>

FourBallAuto::FourBallAuto(DriveSubsystem* subsystem, IntakeSubsystem* intake, ShooterSubsystem* shooter)
    : m_drive{subsystem}
    , m_intake{intake}
    , m_shooter{shooter} {

    AddCommands(
        frc2::ParallelCommandGroup {
            IntakeCommand(m_intake, [this]() {return this->intake_in;}),
            
            frc2::SequentialCommandGroup {
                DriveDistance(m_drive, []() {return 5;}),
                TurnDegrees(m_drive, [](){return -20;}),
                DriveDistance(m_drive, []() {return -(34 / 12); }),
                frc2::InstantCommand([this]() { this->intake_in = true; }),
                ShooterCommand(m_shooter, 
                    [this]() {return this->m_shooter->GetAutoSpeedSetpoint(); },
                    [this]() {return this->m_shooter->GetAutoHoodSetpoint(); }),
                frc2::InstantCommand([this]() { this->intake_in = false; }),
                frc2::ParallelCommandGroup {
                    IntakeCommand(m_intake, [this]() {return this->intake_in;}),

                    frc2::SequentialCommandGroup {
                        TurnDegrees(m_drive, [](){return 45;}),
                        DriveDistance(m_drive, [](){return 10;}),
                        TurnDegrees(m_drive, [](){return -45;}),
                        frc2::InstantCommand([this]() { this->intake_in = true; }),
                        DriveDistance(m_drive, [](){return 7;}),
                        DriveDistance(m_drive, [](){return -(52 / 12);}),
                        TurnDegrees(m_drive, [](){return 45; }),
                        DriveDistance(m_drive, [](){return -(120 / 12);}),
                        ShooterCommand(m_shooter, 
                            [this]() {return this->m_shooter->GetAutoSpeedSetpoint(); },
                            [this]() {return this->m_shooter->GetAutoHoodSetpoint(); }),
                        // Done! :)
                    }
                }
            }
        }



    );
}