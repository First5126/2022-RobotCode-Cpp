#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/ExampleSubsystem.h"
#include "subsystems/DriveSubsystem.h"
#include "subsystems/ClimerSubsystem.h"
#include "subsystems/ShooterSubsystem.h"
#include "subsystems/IntakeSubsystem.h"

class ExampleCommand
    : public frc2::CommandHelper<frc2::CommandBase, ExampleCommand> {
 public:

  explicit ExampleCommand(DriveSubsystem* subsystem);

  //void Initialize() override;
  //bool IsFinished() override;
  //void Execute() override;
  //void End(bool interrupt) override;


 private:
  DriveSubsystem* m_subsystem;
};
