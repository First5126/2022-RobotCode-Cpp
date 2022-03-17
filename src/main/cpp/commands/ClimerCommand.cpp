
#include "commands/ClimerCommand.h"
#include "commands/DriveDistanceCommand.h"

#include "frc2/command/SequentialCommandGroup.h"


#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>

#include <iostream>

ClimerCommand::ClimerCommand(ClimerSubsystem* subsystem,
 std::function<double()> up, std::function<double()> down,
 std::function<double()> up_high, std::function<double()> down_high)
    : m_climer{subsystem}
    , m_up{std::move(up)}
    , m_down{std::move(down)}
    , m_up_high{std::move(up_high)}
    , m_down_high{std::move(down_high)} {
    AddRequirements({subsystem});
}

void ClimerCommand::Execute() {
    m_climer->SetLow(m_up() + ( -m_down()));
    m_climer->SetHigh(m_up_high() + ( - m_down_high() ));
}