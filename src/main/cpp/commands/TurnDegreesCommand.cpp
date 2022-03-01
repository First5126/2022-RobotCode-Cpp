
#include "commands/TurnDegreesCommand.h"
#include <frc/smartdashboard/SmartDashboard.h>

TurnDegrees::TurnDegrees(DriveSubsystem* subsystem, std::function<double()> turn) 
 : m_drive {subsystem}
 , m_turn {std::move(turn)} {

}

void TurnDegrees::Initialize() {
    this->is_done = 0;

    


}

void TurnDegrees::End(bool interrup)  {
    
    

    this->m_left_pid.Reset();
    this->m_right_pid.Reset();

    
}

void TurnDegrees::Execute() {
   

    frc::SmartDashboard::PutNumber("Distance From Goal", 0);
    
}

bool TurnDegrees::IsFinished() {
    
}