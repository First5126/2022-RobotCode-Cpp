#include "DriveAuto.h"

#include <iostream>


using namespace pathplanner;
using namespace Auto;

DriveAuto::DriveAuto(Layer *layer) {
    this->m_layer = layer;

    assert(this->m_layer != nullptr);

    //examplePath = PathPlanner::loadPath("New Path", 3_mps, 3_mps_sq);

    //this->exampleState = this->examplePath.sample(1.2_s);
   
}

DriveAuto::~DriveAuto() {

}

void DriveAuto::update() {

}


// Drive SubSystem

DriveSubsystem::DriveSubsystem(Layer *layer) {
    m_layer = layer;

    assert(m_layer != nullptr);

    std::cout << "[DriveSubSystem] INIT!" << std::endl;
}

DriveSubsystem::~DriveSubsystem() {
    // Nothing (JAMES SHUT UP)
}

void DriveSubsystem::Periodic() {
    // This will run every time it updates
}

void DriveSubsystem::ArcadeDrive(double fwd, double rot) { 
    m_layer->turning_drive_speed = rot;
    m_layer->forward_drive_speed = fwd;
}

void DriveSubsystem::TankDriveVolts(units::volt_t left, units::volt_t right) {
    m_layer->left = left;
    m_layer->right = right;
}

void DriveSubsystem::ResetEncoders() {
    m_layer->resetMotors();
}

double DriveSubsystem::GetAverageEncoderDistance() {
    return (m_layer->left_pos + m_layer->right_pos) / 2.0;
}

frc::Encoder& DriveSubsystem::GetLeftEncoder() {
    frc::Encoder enc();

}

frc::Encoder& DriveSubsystem::GetRightEncoder() {

}

void DriveSubsystem::SetMaxOutput(double maxOutput) {

}

units::degree_t DriveSubsystem::GetHeading() const {

}

double DriveSubsystem::GetTurnRate() {

}

frc::Pose2d DriveSubsystem::GetPose() {

}

frc::DifferentialDriveWheelSpeeds DriveSubsystem::GetWheelSpeeds() {

}

void DriveSubsystem::ResetOdometry(frc::Pose2d pose) {

}