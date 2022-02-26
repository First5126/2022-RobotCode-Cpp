#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/DriveSubsystem.h"

class DrivingAuto
    : public frc2::CommandHelper<frc2::CommandBase, DrivingAuto> {
 public:
  
  explicit DrivingAuto(DriveSubsystem* subsystem);

  

 private:
  DriveSubsystem* m_subsystem;
};
