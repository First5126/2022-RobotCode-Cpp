
#include "commands/ClimerCommand.h"
#include "commands/DriveDistanceCommand.h"

#include "frc2/command/SequentialCommandGroup.h"


#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>

#include <iostream>

ClimerCommand::ClimerCommand(ClimerSubsystem* subsystem, std::function<double()> up, std::function<double()> down)
    : m_climer{subsystem}
    , m_up{std::move(up)}
    , m_down{std::move(down)} {
    
}

void ClimerCommand::Execute() {
    m_climer->Set(m_up() + (1 - m_down()));
}