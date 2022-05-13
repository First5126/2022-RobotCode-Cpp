#include "commands/IntakeCommand.h"
#include <frc/smartdashboard/SmartDashboard.h>

#include <iostream>

IntakeCommand::IntakeCommand(IntakeSubsystem* subsystem, std::function<bool()> overrideFinish)
    : m_intake{subsystem}
    , m_override {std::move(overrideFinish)}  {
        AddRequirements(m_intake);
}

bool IntakeCommand::IsFinished() {
    // limit switch
    if (m_override()) std::cout << "Intake Command Ended!" << std::endl;
    return m_override();
}

void IntakeCommand::Execute() {    
   /*ticks++;

   if (m_override()) {
       this->m_intake->RetractIntake();

       if (ticks % 50) {
           if (this->lastState) {
               this->m_intake->RunIntake();
               this->lastState = false;
           }
           else {
               this->m_intake->StopIntake();
               this->lastState = true;
           }
       }
   }
   else {*/
       this->m_intake->RunIntake();
       this->m_intake->DeployIntake();
       std::cout << "THE INTAKE SHOULD BE OUT!!!" << std::endl;

   //}
    
}

void IntakeCommand::Initialize() {
    this->m_intake->RetractIntake();
}

void IntakeCommand::End(bool interrupt) {
    this->m_intake->RetractIntake();
    this->m_intake->StopAll();
}