// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>

#include "Layer.h"
#include "xbox.h"
#include "drivetrain.h"
#include "rpi_camera.h"
#include "BallTarget.h"

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void TestInit() override;
  void TestPeriodic() override;

 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;

  Layer *m_layer = new Layer();
  
  InputDev::Xbox *m_xbox = new InputDev::Xbox(m_layer);
  OutputDev::DriveTrain *m_drivetrain = new OutputDev::DriveTrain(m_layer);
  InputDev::rpi_camera *m_camera = new InputDev::rpi_camera(m_layer);
  Auto::BallTarget *m_balltarget = new Auto::BallTarget(m_layer);  
};
