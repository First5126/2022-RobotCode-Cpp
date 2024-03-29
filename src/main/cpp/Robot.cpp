// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandScheduler.h>

#include <iostream>

void Robot::RobotInit() {
  std::cout << "ROBOT STARTING..." << std::endl;
  
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want to run during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {
  frc::SmartDashboard::PutNumber("Pressure", m_container.m_compressor.GetPressure().value());
  frc2::CommandScheduler::GetInstance().Run();


  if (LastSend != SentLED && sending_for < 10) {
    this->sending_for++;
    //m_container.leds.Write(SentLED);
  }
  else {
    sending_for = 0;
    LastSend = SentLED;
  }
  

  IsConnected =  m_container.m_shooter.IsConnected();

  if (!IsConnected) SentLED = "P";
  else              SentLED = "c";
}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() {
  
}

void Robot::DisabledPeriodic() {
  SentLED = "c";
}

/**
 * This autonomous runs the autonomous command selected by your {@link
 * RobotContainer} class.
 */
void Robot::AutonomousInit() {
  m_autonomousCommand = m_container.GetAutonomousCommand();

  if (m_autonomousCommand != nullptr) {
    m_autonomousCommand->Schedule();
  }

  
}

void Robot::AutonomousPeriodic() {
  SentLED = "A";
}

void Robot::TeleopInit() {
  // This makes sure that the autonomous stops running when
  // teleop starts running. If you want the autonomous to
  // continue until interrupted by another command, remove
  // this line or comment it out.
  if (m_autonomousCommand != nullptr) {
    m_autonomousCommand->Cancel();
    m_autonomousCommand = nullptr;
  }

  
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic() {
  auto color = table.get()->GetBoolean("IsRedAlliance", false);

  if (color) {
    SentLED = "RC";
  }
  else {
    SentLED = "BC";
  }

}

/**
 * This function is called periodically during test mode.
 */
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
