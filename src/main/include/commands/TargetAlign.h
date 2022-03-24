#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/ShooterSubsystem.h"
#include "subsystems/DriveSubsystem.h"

/**
 * An example command that uses an example subsystem.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class TargetAlign
    : public frc2::CommandHelper<frc2::CommandBase, TargetAlign> {
 public:
  /**
   * Creates a new ExampleCommand.
   *
   * @param subsystem The subsystem used by this command.
   */
  explicit TargetAlign(ShooterSubsystem* shooter, DriveSubsystem* drive);

  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End(bool inter) override;


 private:
  
  double targetDelta = -1;

  ShooterSubsystem* m_shooter;
  DriveSubsystem* m_drive;

  frc::PIDController m_left_pid {0.2, 0.2, 0};

  bool is_done = false;
};
