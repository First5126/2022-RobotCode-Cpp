#include "commands/HoodCommand.h"
#include <frc/smartdashboard/SmartDashboard.h>

#include <iostream>

HoodCommand::HoodCommand(ShooterSubsystem* subsystem, std::function<int()> hood)
    : m_shooter{subsystem}
    , m_hood {std::move(hood)}  {
        AddRequirements(m_shooter);
}

bool HoodCommand::IsFinished() {
    return this->m_shooter->IsHoodAtPos(m_hood());
}

void HoodCommand::Execute() {    
   
    this->m_shooter->SetHoodToPos(m_hood());
    
}

void HoodCommand::Initialize() {
}

void HoodCommand::End(bool interrupt) {

}