#include "Layer.h"
#include "xbox.h"

#include <math.h>
#include <iostream>
#include <math.h>

InputDev::Xbox::Xbox(Layer *layer) {
    m_layer = layer;
    m_controller = new frc::XboxController{0};

    assert(m_layer != NULL);
    assert(m_layer != NULL);
    
    std::cout << "[INPUTDEV]: XBOX CONTROLLER INIT" << std::endl;

}

InputDev::Xbox::Xbox(Layer *layer, uint8_t port) {
    m_layer = layer;
    m_controller = new frc::XboxController{port};

    assert(m_layer != NULL);

    std::cout << "[INPUTDEV]: XBOX CONTROLLER INIT" << std::endl;

}


InputDev::Xbox::~Xbox() {
    // Let go of the pointer
    free(m_controller);
}

void InputDev::Xbox::OutputIntoLayer() {
    double Lx = m_controller->GetRawAxis(3) - m_controller->GetRawAxis(2);
    double Ry = ClampDeadZone(m_controller->GetLeftX(), 0.15);

    m_layer->left_locked = m_controller->GetLeftBumper();
    m_layer->right_locked = m_controller->GetRightBumper();


    m_layer->forward_drive_speed = Lx;
    m_layer->turning_drive_speed = Ry;

    m_layer->GrabBall = m_controller->GetAButton();
    m_layer->intaking = m_controller->GetBButton();
    m_layer->shooting = ClampDeadZone(m_controller->GetRightY(), 0.15);
}

double InputDev::Xbox::ClampDeadZone(double intput, double deadzone) {
    return ((intput >= 0) ? 1.f : -1.f) * ((fabs(intput) > deadzone) ? ((fabs(intput) - deadzone) / (1.f - deadzone)) : 0);
}