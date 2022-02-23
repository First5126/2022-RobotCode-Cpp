#include "shooter.h"
#include "robotbase.h"

using namespace OutputDev;

Shooter::Shooter(Layer* layer) {
    this->m_layer = layer;
    ShooterMotorRight = new TalonFX {11};
    ShooterMotorLeft  = new TalonFX {5};

    IntakeWheel = new TalonSRX {15};

    assert(this->m_layer != nullptr);
    assert(ShooterMotorRight != nullptr);
    assert(ShooterMotorLeft != nullptr);

    ShooterMotorRight->Config_kP(0, 0.25);
    ShooterMotorLeft->Config_kP(0, 0.25);

    ShooterMotorLeft->SetInverted(true);

    ShooterMotorLeft->Follow(*ShooterMotorRight);
}

Shooter::~Shooter() {
    delete ShooterMotorRight;
    delete ShooterMotorLeft;
}

void Shooter::update() {
    m_layer->current_shooting_speed = ShooterMotorRight->GetSelectedSensorVelocity(0);

    ShooterMotorRight->Set(ControlMode::PercentOutput, m_layer->shooting ? m_layer->shooting_percent : 0);

    IntakeWheel->Set(ControlMode::PercentOutput, m_layer->intaking);
}

void Shooter::VelUpdate() {
    m_layer->current_shooting_speed = ShooterMotorRight->GetSelectedSensorVelocity(0);


    if (m_layer->shooting) {
        ShooterMotorRight->Set(ControlMode::Velocity, m_layer->shooting_percent * 10000);
        
    }
    else {
        ShooterMotorRight->Set(ControlMode::PercentOutput, 0);
    }
}