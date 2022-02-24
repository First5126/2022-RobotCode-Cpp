/*
* TEAM 5126 (c) : 2022 FRC Rapid React
* Command Based C++ Robot Code 
* 
* [Default Drive]
*
* DriveSubsystem <== []() {forward} && []() {rotation}
* 
* ## What does this command do?
* Drives the robot with the controller, when no one
* else is talking.
*/ 


#include "commands/DefaultDriveCommand.h"

#include <utility>

DefaultDrive::DefaultDrive(DriveSubsystem* subsystem,
                           std::function<double()> forward,
                           std::function<double()> rotation)
    : m_drive{subsystem},
      m_forward{std::move(forward)},
      m_rotation{std::move(rotation)} {
  AddRequirements({subsystem});
}

void DefaultDrive::Execute() {
  m_drive->ArcadeDrive(m_forward(), m_rotation());
}