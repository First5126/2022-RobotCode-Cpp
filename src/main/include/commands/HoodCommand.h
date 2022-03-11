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
class HoodCommand
    : public frc2::CommandHelper<frc2::CommandBase, HoodCommand> {
 public:
  /**
   * Creates a new ExampleCommand.
   *
   * @param subsystem The subsystem used by this command.
   */
  explicit HoodCommand(ShooterSubsystem* subsystem, std::function<int()> hood);


  void Initialize() override;
  bool IsFinished() override;
  void Execute() override;
  void End(bool interrupt) override;

  //void Initialize() override;
  //void Execute() override;


 private:
  ShooterSubsystem* m_shooter;

  std::function<int()> m_hood;
};
