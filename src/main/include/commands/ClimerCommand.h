#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/ExampleSubsystem.h"
#include "subsystems/DriveSubsystem.h"
#include "subsystems/ClimerSubsystem.h"

/**
 * An example command that uses an example subsystem.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class ClimerCommand
    : public frc2::CommandHelper<frc2::CommandBase, ClimerCommand> {
 public:
  /**
   * Creates a new ExampleCommand.
   *
   * @param subsystem The subsystem used by this command.
   */
  explicit ClimerCommand(ClimerSubsystem* subsystem, std::function<double()> up, std::function<double()> down);

  //void Initialize() override;
  void Execute() override;


 private:
  ClimerSubsystem* m_climer;

  std::function<double()> m_up;
  std::function<double()> m_down;
};
