#include "drivetrain.h"
#include "robotbase.h"
#include <iostream>

OutputDev::DriveTrain::DriveTrain(Layer *layer) {
    m_layer = layer;

    Base::Motors::DriveTrain::rightBack.SetInverted(true);
    Base::Motors::DriveTrain::rightFront.SetInverted(true);

    Base::Motors::DriveTrain::rightBack.Follow(Base::Motors::DriveTrain::rightFront);
    Base::Motors::DriveTrain::leftBack.Follow(Base::Motors::DriveTrain::leftFront);

    assert(m_layer != NULL);

    std::cout << "[OUTPUTDEV]: DRIVE TRAIN INIT" << std::endl;
}

OutputDev::DriveTrain::~DriveTrain() { }

void OutputDev::DriveTrain::update() {
    double Forward = m_layer->forward_drive_speed;
    double Turn = m_layer->turning_drive_speed;

    Drive(Forward + Turn, Forward - Turn);
}

void OutputDev::DriveTrain::Drive(double left, double right) {
    Base::Motors::DriveTrain::leftFront .Set(ControlMode::PercentOutput, left);
    Base::Motors::DriveTrain::rightFront.Set(ControlMode::PercentOutput, right);

    m_layer->left_acc = m_layer->left_vel;
    m_layer->left_vel = Base::Motors::DriveTrain::leftBack.GetSelectedSensorVelocity(1);
    m_layer->left_pos = Base::Motors::DriveTrain::leftBack.GetSelectedSensorPosition(1);
    m_layer->left_acc = m_layer->left_vel - m_layer->left_acc;

    m_layer->right_acc = m_layer->left_vel;
    m_layer->right_vel = Base::Motors::DriveTrain::rightBack.GetSelectedSensorVelocity(1);
    m_layer->right_pos = Base::Motors::DriveTrain::rightBack.GetSelectedSensorPosition(1);
    m_layer->right_acc = m_layer->right_vel - m_layer->right_acc;



    if (m_layer->right_locked) Base::Motors::DriveTrain::rightFront.Set(ControlMode::PercentOutput, (left > 0) ? -0.01 : 0.01);
    if (m_layer->left_locked) Base::Motors::DriveTrain::leftFront.Set(ControlMode::PercentOutput, (right > 0) ? -0.01 : 0.01);
    
}