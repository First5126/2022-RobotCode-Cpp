// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ExampleCommand.h"
#include "commands/DriveDistanceCommand.h"

#include "frc2/command/SequentialCommandGroup.h"


#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>

#include <iostream>

ExampleCommand::ExampleCommand(DriveSubsystem* subsystem)
    : m_subsystem{subsystem} {

    //this->AddCommands( DriveDistance (m_subsystem, [this]() { return 10.0; }));
        
}

/*
void ExampleCommand::Initialize() {

}

void ExampleCommand::Execute() {

}*/