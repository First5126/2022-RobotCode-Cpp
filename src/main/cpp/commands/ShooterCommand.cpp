#include "commands/ShooterCommand.h"
#include <frc/smartdashboard/SmartDashboard.h>

#include <iostream>

ShooterCommand::ShooterCommand(ShooterSubsystem* subsystem, std::function<double()> speed, std::function<int()> hood)
    : m_shooter{subsystem}
    , m_shooting_speed {std::move(speed)}
    , m_hood {std::move(hood)}  {
        AddRequirements(m_shooter);

}

bool ShooterCommand::IsFinished() {
    return !IsBallInShooter;
}

void ShooterCommand::Execute() {    
    this->m_shooter->RunShooter(m_shooting_speed());
    // 5000 limit
    this->m_shooter->SetHoodToPos(m_hood());

    frc::SmartDashboard::PutNumber("Shooting Speed Difference", this->m_shooter->GetShooterSpeed() - m_shooting_speed());

    if (this->m_shooter->IsShooterAtSpeed(m_shooting_speed()) && this->m_shooter->IsHoodAtPos(m_hood())) {
        this->m_shooter->FeedBall();
        //this->m_shooter->RunShooter(0);
        
    }
    else {
        this->m_shooter->StopFeedBall();
    }

    IsBallInShooter = m_shooter->ContainsBall();
}

void ShooterCommand::Initialize() {
    IsBallInShooter = m_shooter->ContainsBall();
}

void ShooterCommand::End(bool interrupt) {
    this->m_shooter->StopAll();
}