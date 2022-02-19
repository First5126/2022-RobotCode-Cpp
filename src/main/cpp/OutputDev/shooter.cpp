#include "shooter.h"
#include "robotbase.h"

using namespace OutputDev;

Shooter::Shooter(Layer* layer) {
    this->m_layer = layer;
    ShooterMotor = new TalonFX {11};
    IntakeWheel = new TalonSRX {15};

    assert(this->m_layer != nullptr);
    assert(ShooterMotor != nullptr);
}

Shooter::~Shooter() {
    delete ShooterMotor;
}

void Shooter::update() {
    ShooterMotor->Set(ControlMode::PercentOutput, m_layer->shooting);

    IntakeWheel->Set(ControlMode::PercentOutput, m_layer->intaking);
}