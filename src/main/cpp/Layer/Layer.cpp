#include "Layer.h"

Layer::Layer() {
    forward_drive_speed = 0;
    turning_drive_speed = 0;
}

Layer::~Layer() {

}

void Layer::OutputToSmartdashboard() {
    
    frc::SmartDashboard::PutNumber("Forward Drive Speed", forward_drive_speed);
    frc::SmartDashboard::PutNumber("Turning Drive Speed", turning_drive_speed);

    frc::SmartDashboard::PutBoolean("Left Locked", left_locked);
    frc::SmartDashboard::PutBoolean("Right Locked", right_locked);

    frc::SmartDashboard::PutNumber("Pi Yaw", pi_yaw);
    frc::SmartDashboard::PutNumber("Pi Pitch", pi_pitch);
    frc::SmartDashboard::PutNumber("Pi Mode", pi_mode);
    frc::SmartDashboard::PutBoolean("Pi Driver Mode", pi_driver_mode);
    frc::SmartDashboard::PutBoolean("Pi Active", pi_active);

        
}