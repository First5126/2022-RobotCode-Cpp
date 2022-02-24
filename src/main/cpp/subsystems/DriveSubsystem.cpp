/*
* TEAM 5126 (c) : 2022 FRC Rapid React
* Command Based C++ Robot Code 
* 
* [Drive Train]
* 
*      |O   |\
* ... [=====] *
* 
* ## What does this subsystem do?
* This subsystem can drive the wheels of the robot.
* It can also get the position of the robot in 2d space!
*/ 

#include "subsystems/DriveSubsystem.h"
#include <iostream>

#include "frc/shuffleboard/Shuffleboard.h"
#include "frc/smartdashboard/SmartDashboard.h"

DriveSubsystem::DriveSubsystem() {
    std::cout << "DriveSubSystem INIT  -  ";
    std::cout << "Checking Motors..." << std::endl;

    // This is very important as we need to make sure our motors
    // are plugged in and working before we can start doing anything. 
    // Basicly if our drivetrain is not working, we dont want to drive
    // the robot at all!

    assert(&LBMotor != nullptr);
    assert(&LFMotor != nullptr);
    assert(&RBMotor != nullptr);
    assert(&RFMotor != nullptr);

    std::cout << "\tWPI_TalonFX\tOK" << std::endl;
    
    assert(&m_left != nullptr);
    assert(&m_right != nullptr);

    std::cout << "\tMotorGroup\tOK" << std::endl;

    bool motors_ok = 
    LFMotor.IsAlive() &&
    LBMotor.IsAlive() &&
    RFMotor.IsAlive() &&
    RBMotor.IsAlive()  ;

    std::cout << "\tMotors\t" << (motors_ok ? "OK" : "FAIL") << std::endl;

    if (!motors_ok) {
        std::cout << "\tMOTOR:" << std::endl;

        std::cout << "\t\tLF\t" << ( LFMotor.IsAlive() ? "OK" : "FAIL" ) << std::endl;
        std::cout << "\t\tLB\t" << ( LBMotor.IsAlive() ? "OK" : "FAIL" ) << std::endl;
        std::cout << "\t\tRF\t" << ( RFMotor.IsAlive() ? "OK" : "FAIL" ) << std::endl;
        std::cout << "\t\tRB\t" << ( RBMotor.IsAlive() ? "OK" : "FAIL" ) << std::endl;
    

        // This can be changed later, but it makes our program fail
        // if any of the motors are not plugged in!
        assert(motors_ok);
    }

}

void DriveSubsystem::Periodic()  {

    // Make sure our our motors are always OK, this helps
    // with electrical problems in the future because we will tell
    // which motors got unplugged!
    bool motors_ok = 
    LFMotor.IsAlive() &&
    LBMotor.IsAlive() &&
    RFMotor.IsAlive() &&
    RBMotor.IsAlive()  ;

    if (!motors_ok) {
        std::cout << "\n\n\nMOTOR FAILED !!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
        std::cout << "\tMOTOR:" << std::endl;

        // Output Which Motor has failed

        std::cout << "\t\tLF\t" << ( LFMotor.IsAlive() ? "OK" : "FAIL" ) << std::endl;
        std::cout << "\t\tLB\t" << ( LBMotor.IsAlive() ? "OK" : "FAIL" ) << std::endl;
        std::cout << "\t\tRF\t" << ( RFMotor.IsAlive() ? "OK" : "FAIL" ) << std::endl;
        std::cout << "\t\tRB\t" << ( RBMotor.IsAlive() ? "OK" : "FAIL" ) << std::endl;
    }
}

void DriveSubsystem::ArcadeDrive(double fwd, double rot) {
    m_drive.ArcadeDrive(fwd, rot);

    frc::SmartDashboard::PutNumber("Forward Drive", fwd);
    frc::SmartDashboard::PutNumber("Turning Drive", rot);
    
}
void DriveSubsystem::TankDriveVolts(units::volt_t left, units::volt_t right) {
    m_left.SetVoltage(left);
    m_right.SetVoltage(right);

    frc::SmartDashboard::PutNumber("Left Volt", left.value());
    frc::SmartDashboard::PutNumber("Right Volt", right.value());
}

void DriveSubsystem::ResetEncoders() {
    ZeroEncoderPos_Left = LFMotor.GetSelectedSensorPosition(1);
    ZeroEncoderPos_right= RFMotor.GetSelectedSensorPosition(1);

}
double DriveSubsystem::GetAverageEncoderDistance() {
    return (this->GetLeftEncoderPos() + this->GetRightEncoderPos()) / 2.0;
}

double DriveSubsystem::GetLeftEncoderPos() {
    return LFMotor.GetSelectedSensorPosition(1) - ZeroEncoderPos_Left;
}
double DriveSubsystem::GetRightEncoderPos() {
    return RFMotor.GetSelectedSensorPosition(1) - ZeroEncoderPos_right;
}

void DriveSubsystem::SetMaxSpeed(double speed) {
    m_drive.SetMaxOutput(speed);
}
units::degree_t DriveSubsystem::GetHeading() const {
    // TODO
}

double DriveSubsystem::GetTurnRate() {
    // TODO
}
frc::Pose2d DriveSubsystem::GetPose() {
    // TODO
}

//frc::DifferentialDriveWheelSpeeds DriveSubsystem::GetWheelSpeeds() {
    //frc::DifferentialDriveWheelSpeeds speed;
    //speed.left  = LFMotor.GetActiveTrajectoryVelocity(1) ;
    //speed.right = RFMotor.GetActiveTrajectoryVelocity(1);
//}
void DriveSubsystem::ResetOdometry(frc::Pose2d pose) {
    m_tacker.ResetPosition(pose, this->GetHeading());
}