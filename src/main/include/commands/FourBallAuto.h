#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>

#include "subsystems/ExampleSubsystem.h"
#include "subsystems/DriveSubsystem.h"
#include "subsystems/ShooterSubsystem.h"
#include "subsystems/IntakeSubsystem.h"

/**
 * An example command that uses an example subsystem.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class FourBallAuto
    : public frc2::CommandHelper<frc2::SequentialCommandGroup, FourBallAuto> {
 public:
  
  explicit FourBallAuto(DriveSubsystem* subsystem, IntakeSubsystem* intake, ShooterSubsystem* shooter);


  bool intake_in = false;

 private:
  DriveSubsystem* m_drive;
  IntakeSubsystem* m_intake;
  ShooterSubsystem* m_shooter;
};
