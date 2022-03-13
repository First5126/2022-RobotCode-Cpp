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
    // First we need to figure out if a ball is currently in the shooter or not.
    // This finds if any ball is in the shooter, so either ball 1 or 2 returns true!
    IsBallInShooter = m_shooter->ContainsBall();

    // We need to then set the shooter speed and the hood
    this->m_shooter->RunShooter(m_shooting_speed());
    this->m_shooter->SetHoodToPos(m_hood());
    
    // Output SmartDashboard
    frc::SmartDashboard::PutBoolean("Shooter Ready", this->m_shooter->IsShooterAtSpeed(m_shooting_speed()));
    frc::SmartDashboard::PutBoolean("Hood Ready", this->m_shooter->IsHoodAtPos(m_hood()));
    frc::SmartDashboard::PutBoolean("Shooting", feedingTicks > 0 && this->m_shooter->ContainsBall());
    frc::SmartDashboard::PutBoolean("Servo", !this->state_change);

    // Try removing the contains ball()
    
    // Figure out when we are VALID to shoot
    if (feedingTicks > 0 && this->m_shooter->ContainsBall()) {
        std::cout << "Valid To Shoot ---------------------------------" << std::endl;

        // Run the feeder motor
        this->m_shooter->FeedBall();    

        // Wipe the servo
        ticks++;
        if (ticks % 30) this->state_change = !this->state_change;        
        this->m_shooter->acuateServo(this->state_change ? 0.5 : -1);

        // Make sure we only take a bit of time to acually send the ball
        feedingTicks--;
    }
    else {

        // Stop and reset all the things
        this->m_shooter->StopFeedBall();
        this->m_shooter->acuateServo(0.5);

        this->state_change = false;
        feedingTicks = 0;
        ticks = 0;
    }

    // We need to know if the shooter and hood is at the speed
    if (this->m_shooter->IsShooterAtSpeed(m_shooting_speed()) && this->m_shooter->IsHoodAtPos(m_hood())) {
        
        // We then need to know if we are valid for 5 ticks (1/10 of a second)
        // Then we are ready to feed the ball
        if (validPeriod > 4) {
            feedingTicks = 5;
        }

        validPeriod++;
    }
    else {
        // If we are not valid for even 1 tick, we need to reset our counter
        validPeriod = 0;
    }
    
    // We need to also wait for 1 second after there is no ball to stop the shooter 
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
    ticks = 0;
}