#include "BallTarget.h"
#include <math.h>

#include <iostream>

using namespace Auto;

BallTarget::BallTarget(Layer *layer) {
    m_layer = layer;

    m_pidController.SetPID(
        0.1, // P
        0.0, // I
        0.0  // D
    );

    assert(m_layer != NULL);

    std::cout << "[AUTO]: BALL TARGET INIT" << std::endl;
}

BallTarget::~BallTarget() {
}

void BallTarget::update() {
    m_pidController.SetSetpoint(m_layer->pi_yaw);
}

void BallTarget::OutputIntoLayer() {
    m_layer->turning_drive_speed = std::clamp(m_pidController.Calculate(m_layer->pi_yaw) / 100., -1., 1.);
}