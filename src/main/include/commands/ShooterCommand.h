#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/ShooterSubsystem.h"


/**
 * An example command that uses an example subsystem.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class ShooterCommand
    : public frc2::CommandHelper<frc2::CommandBase, ShooterCommand> {
 public:
  /**
   * Creates a new ExampleCommand.
   *
   * @param subsystem The subsystem used by this command.
   */
  explicit ShooterCommand(ShooterSubsystem* subsystem, std::function<double()> speed, std::function<int()> hood);


  void Initialize() override;
  bool IsFinished() override;
  void Execute() override;
  void End(bool interrupt) override;

  //void Initialize() override;
  //void Execute() override;


 private:
  ShooterSubsystem* m_shooter;

  std::function<double()> m_shooting_speed;
  std::function<int()> m_hood;

  int donefor = 0;
  int validPeriod = 0;
  int feedingTicks = 0;

  int ticks = 0;
  bool state_change = false;

  int total_ticks = 0;

  bool IsBallInShooter = 0;
  bool IsCurrentlyShooting = 0;
};
