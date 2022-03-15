#pragma once

#include <frc2/command/SubsystemBase.h>
#include <string.h>

#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableInstance.h"
#include "networktables/NetworkTableValue.h"
#include "networktables/NetworkTableType.h"
#include "networktables/NetworkTableInstance.h"

class VisionSubsystem : public frc2::SubsystemBase {
 public:
  VisionSubsystem();

  enum Mode {
      DRIVER = -1,
      BLUE_BALL,
      RED_BALL,
      TAPE
  };

  
  void Periodic() override;

  bool IsConnected();

  void SetMode(Mode mode);
  int GetMode();

  bool IsDetectingBall();
  double GetBallYaw();
  double GetBallPitch();
  double GetBallDistance();

  bool IsDetectingTape();
  double GetTapeYaw();
  double GetTapePitch();
  double GetTapeDistance();
  

 private:

  double GetValueFromPi(std::string value);

  std::shared_ptr<nt::NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");

  bool ObjectInFrame = false;
  double latency = 0;
  
  int CurrentMode = 0;

  double Yaw = 0;
  double Pitch = 0;  

  const std::string PiName = "limelight";
  const std::string CameraName = "";
};
