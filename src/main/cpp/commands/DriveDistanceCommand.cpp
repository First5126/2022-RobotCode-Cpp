#include "commands/DriveDistanceCommand.h"

#include <iostream>

DriveDistance::DriveDistance(DriveSubsystem* subsystem, std::function<double()> forward)
    : m_drive{subsystem},
    m_forward {std::move(forward)} {

    AddRequirements(m_drive);
}

void DriveDistance::Initialize() {
    std::cout << "PAIN PAIN PAOIN" << std::endl;
    this->is_done = 0;

    this->EncoderStartLeftValue = m_drive->GetLeftEncoderPos();
    this->EncoderStartRightValue = m_drive->GetRightEncoderPos();

    this->EncoderSetLeftValue = m_drive->CalcualteDriveEncoder(m_forward());
    this->EncoderSetRightValue = m_drive->CalcualteDriveEncoder(m_forward()); 

    
}

void DriveDistance::End(bool interrup)  {
    
    this->EncoderStartLeftValue = 0;
    this->EncoderStartRightValue = 0;

    this->EncoderSetLeftValue = 0;
    this->EncoderSetRightValue = 0;

    
}

void DriveDistance::Execute() {
    double RealEncoderLeft = this->EncoderSetLeftValue + this->EncoderStartLeftValue;
    double RealEncoderRight = this->EncoderSetRightValue + this->EncoderStartRightValue;

    if (RealEncoderLeft >= m_drive->GetLeftEncoderPos() || RealEncoderRight >= m_drive->GetRightEncoderPos()) {
        m_drive->ArcadeDrive(0.4, 0);
    }

    else if (RealEncoderLeft <= m_drive->GetLeftEncoderPos() || RealEncoderRight <= m_drive->GetRightEncoderPos()) {
        m_drive->ArcadeDrive(-0.4, 0);
    }

    
}

bool DriveDistance::IsFinished() {
    std::cout << "Test" << std::endl;
    double RealEncoderLeft = this->EncoderSetLeftValue + this->EncoderStartLeftValue;
    double RealEncoderRight = this->EncoderSetRightValue + this->EncoderStartRightValue;

    auto within =  [this](double within_amount, double first, double second) {
        double DiffernenceAmount = fabs(first - second);
        return within_amount >= DiffernenceAmount;
    };

    double WithinValue = 1000;
    if (within(WithinValue, m_drive->GetLeftEncoderPos(), RealEncoderLeft) && within(WithinValue, m_drive->GetRightEncoderPos(), RealEncoderRight)) {
        return true;
    }

    return false;
}