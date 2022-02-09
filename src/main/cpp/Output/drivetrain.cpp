#include "drivetrain.h"
#include "robotbase.h"

OutputDev::DriveTrain::DriveTrain(CompLayer *layer) {
    m_layer = layer;

    Base::Motors::DriveTrain::rightBack.SetInverted(true);
    Base::Motors::DriveTrain::rightFront.SetInverted(true);
}

OutputDev::DriveTrain::~DriveTrain() { }

void OutputDev::DriveTrain::update() {
    double Forward = m_layer->forward_drive_speed;
    double Turn = m_layer->turning_drive_speed;

    Drive(Forward + Turn, Forward - Turn);
}

void OutputDev::DriveTrain::Drive(double left, double right) {
    Base::Motors::DriveTrain::leftFront.Set (ControlMode::PercentOutput, left);
    Base::Motors::DriveTrain::leftBack.Set  (ControlMode::PercentOutput, left);
    Base::Motors::DriveTrain::rightFront.Set(ControlMode::PercentOutput, right);
    Base::Motors::DriveTrain::rightBack.Set (ControlMode::PercentOutput, right);
}