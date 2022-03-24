#include "commands/ClimerHome.h"
#include "commands/DriveDistanceCommand.h"
#include "frc2/command/SequentialCommandGroup.h"
#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>

#include <iostream>

ClimerHome::ClimerHome(ClimerSubsystem* climer)
    : m_climer{climer} {
    
}

void ClimerHome::Initialize() {
    m_climer->resetAll();
}

bool ClimerHome::IsFinished() {
    for (int i = 0; i < 4; i ++) {
        if (hominglist[i]) continue;
        else return false;
    }

    return true;
}

void ClimerHome::Execute() {
    for (int i = 0; i < 4; i ++) {
        if (!hominglist[i]) {
            int diff = m_climer->GetMotorIdEncoder(i);
            m_climer->ResetMotorId(i);

            if (diff > 0) {
                m_climer->SetMotorId(i, -0.3);
            }
            else {
                m_climer->SetMotorId(i, 0);
                hominglist[i] = true;
            }
        }
    }
}

void ClimerHome::End(bool interrupt) {
    for (int i = 0; i < 4; i++) {
        m_climer->SetMotorId(i, 0);
        m_climer->ResetMotorId(i);
    }
}

