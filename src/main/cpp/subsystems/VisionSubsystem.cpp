#include "subsystems/VisionSubsystem.h"

#include <iostream>

VisionSubsystem::VisionSubsystem() {
    m_table = nt::NetworkTableInstance::GetDefault();

    std::cout << "VisionSubsystem\tOK" << std::endl;    
}
  
void VisionSubsystem::Periodic() {
    this->latency = GetValueFromPi("latencyMillis");
    this->Yaw = GetValueFromPi("targetYaw");
    this->Pitch = GetValueFromPi("targetPitch");
    this->CurrentMode = GetValueFromPi("pipelineIndex");

    this->ObjectInFrame = Yaw != 0 || Pitch != 0;  
}

bool VisionSubsystem::IsConnected() {
    return this->latency > 0;
}

void VisionSubsystem::SetMode(Mode mode) {
    std::string NetworkTablesRequest = "/" + PiName + "/" + CameraName + "/pipelineIndex";
    m_table.GetEntry(NetworkTablesRequest).SetDouble(mode);

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
    // TODO: Calculate the distance of the ball based on the pitch
}

double VisionSubsystem::GetValueFromPi(std::string value) {
    std::string NetworkTablesRequest = "/" + PiName + "/" + CameraName + "/" + value;

    return m_table.GetEntry(NetworkTablesRequest).GetDouble(0);
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
    // TODO: Calculate the distance of the tap from the pitch and yaw
}