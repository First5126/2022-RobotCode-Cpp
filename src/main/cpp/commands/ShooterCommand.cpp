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
    return this->donefor > 50;
}

void ShooterCommand::Execute() {    
    this->m_shooter->RunShooter(m_shooting_speed());
    // 5000 limit
    this->m_shooter->SetHoodToPos(m_hood());

    frc::SmartDashboard::PutNumber("Shooting Speed Difference", this->m_shooter->GetShooterSpeed() - m_shooting_speed());

    if (feedingTicks > 0 && this->m_shooter->ContainsBall()) {
        this->m_shooter->FeedBall();
        this->m_shooter->acuateServo(-1);

        std::cout << "Feeding Ball!" << std::endl;
        feedingTicks--;
    }
    else {
        this->m_shooter->StopFeedBall();
        this->m_shooter->acuateServo(0.5);
        feedingTicks = 0;
    }

    //std::cout << "validPeroid: " << validPeriod
    //<< " " << this->m_shooter->IsShooterAtSpeed(m_shooting_speed()) << ":" << this->m_shooter->IsHoodAtPos(m_hood()) << std::endl;
    
    if (this->m_shooter->IsShooterAtSpeed(m_shooting_speed()) && this->m_shooter->IsHoodAtPos(m_hood())) {
        validPeriod++;

        if (validPeriod > 4) {
            feedingTicks = 5;
            std::cout << "Valid To Shoot ---------------------------------" << std::endl;
        }  

        
    }
    else {
        validPeriod = 0;        
    }

    IsBallInShooter = m_shooter->ContainsBall();

    //std::cout << "Ball: " << IsBallInShooter << " : " << this->donefor << " Shooting!" << std::endl;

    if (!IsBallInShooter) this->donefor++;
    else                 this->donefor = 0;
}

void ShooterCommand::Initialize() {
    IsBallInShooter = m_shooter->ContainsBall();
}

void ShooterCommand::End(bool interrupt) {
    this->m_shooter->StopAll();
    this->m_shooter->acuateServo(0.5);

    validPeriod = 0;
    feedingTicks = 0;
}