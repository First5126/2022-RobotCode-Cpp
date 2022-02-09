#include "Layer.h"
#include "xbox.h"

#include <math.h>
#include <iostream>

Input::Xbox::Xbox(CompLayer *layer) {
    m_layer = layer;
    m_controller = new frc::XboxController{0};
}

Input::Xbox::Xbox(CompLayer *layer, uint8_t port) {
    m_layer = layer;
    m_controller = new frc::XboxController{port};
}


Input::Xbox::~Xbox() {
    // Let go of the pointer
    free(m_controller);
}

void Input::Xbox::OutputIntoLayer() {
    double Lx = m_controller->GetLeftY();
    double Ry = m_controller->GetRightX();

    Lx = (2.f - log(Lx)) / 2.f;
    Ry = (2.f - log(Ry)) / 2.f;

    std::cout << "DriveTrain: " << Lx << ", " << Ry << std::endl; 

    //m_layer->forward_drive_speed = Lx;
    //m_layer->turning_drive_speed = Ry;
}