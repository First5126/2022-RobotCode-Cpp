#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/ExampleSubsystem.h"
#include "subsystems/DriveSubsystem.h"
#include "subsystems/ClimerSubsystem.h"
#include "subsystems/ShooterSubsystem.h"
#include "subsystems/IntakeSubsystem.h"

class ClimerHome
    : public frc2::CommandHelper<frc2::CommandBase, ClimerHome> {
 public:

  explicit ClimerHome(ClimerSubsystem* subsystem);

  void Initialize() override;
  bool IsFinished() override;
  void Execute() override;
  void End(bool interrupt) override;

  

 private:
  ClimerSubsystem* m_climer;

  bool hominglist[4] = {0, 0, 0, 0};
};
