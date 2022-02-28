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

IntakeSubsystem::IntakeSubsystem() {
    std::cout << "IntakeSubsystem init - Checking Motors..." << std::endl;
    this->IntakeMotor = new rev::CANSparkMax(0, rev::CANSparkMaxLowLevel::MotorType::kBrushless);

    assert(this->IntakeMotor != nullptr);
    std::cout << "Motors\tOK" << std::endl;
}

void IntakeSubsystem::Periodic() {
    ;
}

void IntakeSubsystem::DeployIntake() {
    // TODO: Switch the state of the pistons
}

void IntakeSubsystem::RetractIntake() {
    // TODO: Switch the state of the pistions
}

void IntakeSubsystem::ToggleIntake() {
    // TODO: Switch the state of the pistions
}

void IntakeSubsystem::RunIntake() {
    this->IntakeMotor->Set(1);
}

void IntakeSubsystem::StopIntake() {
    this->IntakeMotor->Set(0);
}

void IntakeSubsystem::StopAll() {
    this->IntakeMotor->Set(0);
}