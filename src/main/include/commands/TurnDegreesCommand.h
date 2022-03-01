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
  explicit TurnDegrees(DriveSubsystem* subsystem, std::function<double()> forward);

  void Initialize() override;
  void Execute() override;
  void End(bool interrup) override;
  bool IsFinished() override;


 private:
  DriveSubsystem* m_drive;

  bool is_done = false;

  std::function<double()> m_turn;

  double init_angle = 0;
  double target_angle = 0;

  frc::PIDController m_left_pid {0.000014, 0.00002, 0};
  frc::PIDController m_right_pid {0.000014, 0.00002, 0};
};
