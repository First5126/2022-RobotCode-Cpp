/*
* TEAM 5126 (c) : 2022 FRC Rapid React
* Command Based C++ Robot Code 
* 
* [Intake]
* 
*       |\
* [=====] *
* 
* ## What does this subsystem do?
* This subsystem can extend or retract the intake.
* It can also run the intake, or stop it.
*/ 

#include "subsystems/IntakeSubsystem.h"
#include <iostream>
#include "frc/smartdashboard/SmartDashboard.h"

IntakeSubsystem::IntakeSubsystem() {
    std::cout << "IntakeSubsystem init - Checking Motors..." << std::endl;
    this->IntakeMotor = new rev::CANSparkMax(35, rev::CANSparkMaxLowLevel::MotorType::kBrushless);

    assert(this->IntakeMotor != nullptr);
    std::cout << "Motors\tOK" << std::endl;

    this->m_arm.Set(frc::DoubleSolenoid::kForward);

    frc::SmartDashboard::PutBoolean("Running Intake", false);
    frc::SmartDashboard::PutBoolean("Intake", false);


}

void IntakeSubsystem::Periodic() {
    ;
}

void IntakeSubsystem::DeployIntake() {
    this->IntakeState = true;
    this->m_arm.Set(frc::DoubleSolenoid::kReverse);

    frc::SmartDashboard::PutBoolean("Intake", true);
}

void IntakeSubsystem::RetractIntake() {
    this->IntakeState = false;
    this->m_arm.Set(frc::DoubleSolenoid::kForward);

    frc::SmartDashboard::PutBoolean("Intake", false);
}

void IntakeSubsystem::ToggleIntake() {
    this->m_arm.Set(this->IntakeState ? frc::DoubleSolenoid::kReverse : frc::DoubleSolenoid::kForward );
}

void IntakeSubsystem::RunIntake() {
    this->IntakeMotor->Set(1);

    frc::SmartDashboard::PutBoolean("Running Intake", true);
}

void IntakeSubsystem::StopIntake() {
    this->IntakeMotor->Set(0);

    frc::SmartDashboard::PutBoolean("Running Intake", false);
}

void IntakeSubsystem::StopAll() {
    this->IntakeMotor->Set(0);

    frc::SmartDashboard::PutBoolean("Running Intake", false);

}

bool IntakeSubsystem::GetIntakeState() {
    return !this->intake_in.Get();
}