#include "subsystems/VisionSubsystem.h"

#include <iostream>

VisionSubsystem::VisionSubsystem() {
    
    std::cout << "VisionSubsystem\tOK" << std::endl;    
}
  
void VisionSubsystem::Periodic() {
    this->latency = GetValueFromPi("latencyMillis");
    this->Yaw = GetValueFromPi("tx");
    this->Pitch = GetValueFromPi("ty");
    this->CurrentMode = GetValueFromPi("pipeline");

    this->ObjectInFrame = Yaw != 0 || Pitch != 0;  
}

bool VisionSubsystem::IsConnected() {
    return this->latency > 0;
}

void VisionSubsystem::SetMode(Mode mode) {
    

    CurrentMode = mode;
}
int VisionSubsystem::GetMode() {
    return CurrentMode;
}

bool VisionSubsystem::IsDetectingBall() {
    return ObjectInFrame;
}

double VisionSubsystem::GetBallYaw() {
    return Yaw;
}
double VisionSubsystem::GetBallPitch() {
    return Pitch;
}

double VisionSubsystem::GetBallDistance() {
  
}

double VisionSubsystem::GetValueFromPi(std::string value) {
    std::string NetworkTablesRequest = "/" + PiName + CameraName + "/" + value;

    return table->GetNumber(value, 0.0);
}

bool VisionSubsystem::IsDetectingTape() {
    return this->ObjectInFrame;
}

double VisionSubsystem::GetTapeYaw() {
    return this->Yaw;
}

double VisionSubsystem::GetTapePitch() {
    return this->Pitch;
}

double VisionSubsystem::GetTapeDistance() {
    double LimeLightHight = 22.75;
    double TargetHight = 103;
    double LimelightAngle = 30; // degrees

    double angleToGoalDegrees = LimelightAngle + Pitch; 
    double angleToGoalRadians = angleToGoalDegrees * (3.14159 / 180.0);

    double Distance = (TargetHight - LimeLightHight) / std::tan(angleToGoalRadians);

    return Distance - (15.5 + 22);
}