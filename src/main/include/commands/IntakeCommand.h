#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/IntakeSubsystem.h"

/**
 * An example command that uses an example subsystem.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class IntakeCommand
    : public frc2::CommandHelper<frc2::CommandBase, IntakeCommand> {
 public:
  /**
   * Creates a new ExampleCommand.
   *
   * @param subsystem The subsystem used by this command.
   */
  explicit IntakeCommand(IntakeSubsystem* subsystem, std::function<bool()> overrideFinish);


  void Initialize() override;
  bool IsFinished() override;
  void Execute() override;
  void End(bool interrupt) override;

  //void Initialize() override;
  //void Execute() override;


 private:
  IntakeSubsystem* m_intake;

  bool lastState = false;

  int ticks = 0;

  std::function<bool()> m_override;
};
