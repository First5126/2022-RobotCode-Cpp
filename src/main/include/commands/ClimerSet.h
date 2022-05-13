#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/ExampleSubsystem.h"
#include "subsystems/DriveSubsystem.h"
#include "subsystems/ClimerSubsystem.h"
#include "subsystems/ShooterSubsystem.h"
#include "subsystems/IntakeSubsystem.h"

class ClimerSet
    : public frc2::CommandHelper<frc2::CommandBase, ClimerSet> {
 public:

  explicit ClimerSet(ClimerSubsystem* climer, std::function<double()> setlow, std::function<double()> sethigh);

  void Initialize() override;
  bool IsFinished() override;
  void Execute() override;
  void End(bool interrupt) override;

  int constructPoint(double input, int id);

  bool within(double point, double number);

 private:
  ClimerSubsystem* m_climer;
  std::function<double()> m_setlow;
  std::function<double()> m_sethigh;


  int setpoint_list[4] = {
       290204,
       302784,
       381532,
       380074,
       
  };


};
