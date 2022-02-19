#include "intake.h"
#include "robotbase.h"

using namespace OutputDev;

Intake::Intake(Layer* layer) {
    this->m_layer = layer;

    IntakeMotor = new rev::CANSparkMax {20, rev::CANSparkMaxLowLevel::MotorType::kBrushless};

    assert(this->m_layer != nullptr);
    assert(IntakeMotor != nullptr);
}

Intake::~Intake() {
    delete IntakeMotor;
}

void Intake::update() {
    if (m_layer->intaking) IntakeMotor->Set(0);
    else                   IntakeMotor->Set(0);
}