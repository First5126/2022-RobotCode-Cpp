#include "drivetrain.h"
#include "robotbase.h"
#include <iostream>

OutputDev::DriveTrain::DriveTrain(Layer *layer) {
    m_layer = layer;

    assert(Base::Motors::DriveTrain::leftBack   != nullptr);
    assert(Base::Motors::DriveTrain::leftFront  != nullptr);
    assert(Base::Motors::DriveTrain::rightBack  != nullptr);
    assert(Base::Motors::DriveTrain::rightFront != nullptr);



    Base::Motors::DriveTrain::rightBack->SetInverted(true);
    Base::Motors::DriveTrain::rightFront->SetInverted(true);

    Base::Motors::DriveTrain::rightBack->Follow(*Base::Motors::DriveTrain::rightFront);
    Base::Motors::DriveTrain::leftBack->Follow(*Base::Motors::DriveTrain::leftFront);

    this->m_drive = new frc::DifferentialDrive (*Base::Motors::DriveTrain::leftFront, *Base::Motors::DriveTrain::rightFront);

    assert(m_layer != NULL);

    std::cout << "[OUTPUTDEV]: DRIVE TRAIN INIT" << std::endl;
}

OutputDev::DriveTrain::~DriveTrain() { }

void OutputDev::DriveTrain::update() {

    Drive(m_layer->forward_drive_speed, m_layer->turning_drive_speed);

}

void OutputDev::DriveTrain::Drive(double left, double right) {

    if (m_layer->IsMotorsNeedingReset()) {
        Base::Motors::DriveTrain::leftBack->SetSelectedSensorPosition(0, 1);
        Base::Motors::DriveTrain::rightBack->SetSelectedSensorPosition(0, 1);
        Base::Motors::DriveTrain::leftFront->SetSelectedSensorPosition(0, 1);
        Base::Motors::DriveTrain::rightFront->SetSelectedSensorPosition(0, 1);
    }

    m_drive->ArcadeDrive(left, right);

    double left_100ms = m_layer->left_vel;
    m_layer->left_vel = Base::Motors::DriveTrain::leftBack->GetSelectedSensorVelocity(1);
    m_layer->left_pos = Base::Motors::DriveTrain::leftBack->GetSelectedSensorPosition(1);
    
    double accel = m_layer->left_vel - left_100ms;
    m_layer->left_acc = (accel > m_layer->left_acc) ? accel : m_layer->left_acc;

    double right_100ms = m_layer->left_vel;
    m_layer->right_vel = Base::Motors::DriveTrain::rightBack->GetSelectedSensorVelocity(1);
    m_layer->right_pos = Base::Motors::DriveTrain::rightBack->GetSelectedSensorPosition(1);
    
    accel = m_layer->left_vel - left_100ms;
    m_layer->right_acc = (accel > m_layer->left_acc) ? accel : m_layer->left_acc;


    if (m_layer->right_locked) Base::Motors::DriveTrain::rightFront->Set(ControlMode::PercentOutput, (left > 0) ? -0.01 : 0.01);
    if (m_layer->left_locked) Base::Motors::DriveTrain::leftFront->Set(ControlMode::PercentOutput, (right > 0) ? -0.01 : 0.01);
    
}