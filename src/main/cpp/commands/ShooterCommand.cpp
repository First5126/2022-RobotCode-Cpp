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
    return this->donefor > 30 || m_shooter->GetCommandState();
}

void ShooterCommand::Execute() {    
    

    // We need to then set the shooter speed and the hood
    if (!this->m_shooter->GetAutoSpinupState()) {
        this->m_shooter->RunShooter(m_shooting_speed());
        this->m_shooter->SetHoodToPos(m_hood());
    }
    
    
    // Output SmartDashboard
    frc::SmartDashboard::PutBoolean("Shooting", feedingTicks > 0);
    frc::SmartDashboard::PutBoolean("Servo", this->state_change);

    // Try removing the contains ball()
    
    // Figure out when we are VALID to shoot
    if (feedingTicks > 0) {
        //std::cout << "Shooting Ball!" <<  std::endl;

        if (m_shooter->ContainsShootingBall()) {
            frc::SmartDashboard::PutNumber("Shot Time", total_ticks / 50.);
            
            // Wipe the servo
            ticks++;
            if (ticks % 40 == 0) { 
                this->state_change = !this->state_change;  
                std::cout << "[ERROR]: Ball stuck!" << std::endl;
            }
            this->m_shooter->acuateServo(this->state_change ? 0.5 : -1);
        }
        else {
            this->m_shooter->acuateServo(0.5);
        }
       
        // Run the feeder motor
        this->m_shooter->FeedBall();    

        // Make sure we only take a bit of time to acually send the ball
        feedingTicks--;
    }
    else {
        //std::cout << "Spinning up Shooter ----- " << std::endl;

        // Stop and reset all the things
        this->m_shooter->StopFeedBall();
        
        if (!m_shooter->ContainsShootingBall())
            this->m_shooter->acuateServo(0.5);

        this->state_change = false;
        feedingTicks = 0;
        ticks = 0;
    }

    // We need to know if the shooter and hood is at the speed
    if ((this->m_shooter->IsShooterAtSpeed(m_shooting_speed()) && this->m_shooter->IsHoodAtPos(m_hood())) || m_shooter->GetAutoSpinupState()) {
        std::cout << "At Speed (waiting) -- " << validPeriod << " X: " << feedingTicks << std::endl;
        // We then need to know if we are valid for 5 ticks (1/10 of a second)
        // Then we are ready to feed the ball
        if (validPeriod > 4) {
            feedingTicks = 10;
        }

        validPeriod++;
    }
    else {
        // If we are not valid for even 1 tick, we need to reset our counter
        validPeriod = 0;
    }

    // First we need to figure out if a ball is currently in the shooter or not.
    // This finds if any ball is in the shooter, so either ball 1 or 2 returns true!
    IsBallInShooter = m_shooter->ContainsBall();
    
    // We need to also wait for 1 second after there is no ball to stop the shooter 
    if (!IsBallInShooter) this->donefor++;
    else                 this->donefor = 0;

    total_ticks++;
}

void ShooterCommand::Initialize() {
    IsBallInShooter = m_shooter->ContainsBall();
    total_ticks = 0;

    if (m_shooter->ContainsShootingBall()) {
        m_shooter->acuateServo(-1);
        std::cout << "Setting Servo" << std::endl;
    }
    
}

void ShooterCommand::End(bool interrupt) {
    
    if (!this->m_shooter->GetAutoSpinupState())
        this->m_shooter->StopAll();
    
    this->m_shooter->acuateServo(0.5);

    //frc::SmartDashboard::PutBoolean("Shooter Ready", false);
    frc::SmartDashboard::PutBoolean("Shooting", false);
    frc::SmartDashboard::PutBoolean("Servo", false);

    std::cout << "Command ended!" << std::endl;
    

    validPeriod = 0;
    feedingTicks = 0;
    total_ticks = 0;
    ticks = 0;
}