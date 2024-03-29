
#include "commands/ClimerSet.h"
#include <iostream>

ClimerSet::ClimerSet(ClimerSubsystem* climer, std::function<double()> setlow, std::function<double()> sethigh)
    : m_climer{climer}
    , m_setlow{setlow}
    , m_sethigh{sethigh}
{
    AddRequirements({climer});   
}

void ClimerSet::End(bool inter) {

}

bool ClimerSet::IsFinished() {
    for (int i = 0; i < 4; i++) {
        if (!within(m_climer->GetMotorIdEncoder(i), this->constructPoint(i > 2 ? m_sethigh() : m_setlow(), i))) {
            return false;
        }
    }
    return true;
}

void ClimerSet::Initialize() {
    std::cout << "Init: " << this->constructPoint(0 > 2 ? m_sethigh() : m_setlow(), 0) << std::endl;
}

void ClimerSet::Execute() {
    for (int i = 0; i < 4; i++) {
        int newpoint = this->constructPoint(i > 2 ? m_sethigh() : m_setlow(), i);
        int currentpoint = m_climer->GetMotorIdEncoder(i);

        int diff = abs(newpoint - currentpoint);

        if (!within(currentpoint, newpoint)) {
            double speed = 0;
            
            if (newpoint > currentpoint) {

                if (diff < 20000) {
                    speed = 0.10;
                }
                else {
                    speed = 0.8;
                }
            }
            else {
                if (diff < 20000) {
                    speed = -0.10;
                }
                else {
                    speed = -0.8;
                }
            }

            m_climer->SetMotorId(i, speed);

            std::cout << "Motor id: " << i << " : " << speed << " --> " <<  newpoint << " | " << diff << std::endl;

        }
        else {
            m_climer->SetMotorId(i, 0);
        }
    }

}

bool ClimerSet::within(double point, double number) {
    double diff = fabs(point - number);

    return diff < 5000;
}

int ClimerSet::constructPoint(double input, int id) {
    double normal_input = (input + 1.0) / 2.0; // 0 -- 1

    int constPoint = this->setpoint_list[id];

    return (int)(normal_input * (double)constPoint);
}