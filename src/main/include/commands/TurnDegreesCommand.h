#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/ExampleSubsystem.h"
#include "subsystems/DriveSubsystem.h"

/**
 * An example command that uses an example subsystem.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class TurnDegrees
    : public frc2::CommandHelper<frc2::CommandBase, TurnDegrees> {
 public:
  /**
   * Creates a new TurnDegrees.
   *
   * @param subsystem The subsystem used by this command.
   */
  explicit TurnDegrees(DriveSubsystem* subsystem);

  void Initialize() override;
  void Execute() override;


 private:
  DriveSubsystem* m_subsystem;
};
