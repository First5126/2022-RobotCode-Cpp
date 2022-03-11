#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/DriveSubsystem.h"

class DriveDistance
    : public frc2::CommandHelper<frc2::CommandBase, DriveDistance> {
 public:
  
   /**
   * Creates a new DriveDistance.
   *
   * @param subsystem The drive subsystem this command wil run on.
   * @param forward The control input for driving forwards/backwards in ft
   */
   explicit DriveDistance(DriveSubsystem* subsystem, std::function<double()> forward);

   void Initialize() override;
   void Execute() override;
   bool IsFinished() override;

   void End(bool interrup) override;

 private:
  DriveSubsystem* m_drive;

  bool is_done = false;

  std::function<double()> m_forward;

  double EncoderSetLeftValue = 0;
  double EncoderSetRightValue = 0;

  double EncoderStartLeftValue = 0;
  double EncoderStartRightValue = 0;

  double Ku = 0.001;
  double time = 1;

  //frc::PIDController m_left_pid  {Ku * 0.6, (1.2 * time) / 0.5, (3 * Ku * time) / 40.0};
  //frc::PIDController m_right_pid {Ku * 0.6, (1.2 * time) / 0.5, (3 * Ku * time) / 40.0};

  //frc::PIDController m_left_pid  {0.4, 0.004, 0.0015};
  //frc::PIDController m_right_pid {0.4, 0.004, 0.0015};
};
