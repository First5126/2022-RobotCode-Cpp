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
#include <math.h>

#include "frc/shuffleboard/Shuffleboard.h"
#include "frc/AnalogGyro.h"
#include "frc/smartdashboard/SmartDashboard.h"

DriveSubsystem::~DriveSubsystem() {
    std::cout << "Deconstruct!" << std::endl;
}

bool DriveSubsystem::CheckMotors() {
    bool motors_ok = 
    LFMotor.GetBusVoltage() > 10 &&
    LBMotor.GetBusVoltage() > 10 &&
    RFMotor.GetBusVoltage() > 10 &&
    RBMotor.GetBusVoltage() > 10 ;

    if (!motors_ok) {
        std::cout << "\n\n\nMOTOR FAILED !!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
        std::cout << "\tMOTOR:" << std::endl;

        // Output Which Motor has failed

        std::cout << "\t\tLF\t" << ( LFMotor.GetBusVoltage() > 10 ? "OK" : "FAIL" ) << std::endl;
        std::cout << "\t\tLB\t" << ( LBMotor.GetBusVoltage() > 10 ? "OK" : "FAIL" ) << std::endl;
        std::cout << "\t\tRF\t" << ( RFMotor.GetBusVoltage() > 10 ? "OK" : "FAIL" ) << std::endl;
        std::cout << "\t\tRB\t" << ( RBMotor.GetBusVoltage() > 10 ? "OK" : "FAIL" ) << std::endl;
    }
}

DriveSubsystem::DriveSubsystem() {
    std::cout << "DriveSubSystem INIT  -  ";
    std::cout << "Checking Motors..." << std::endl;

    // This is very important as we need to make sure our motors
    // are plugged in and working before we can start doing anything. 
    // Basicly if our drivetrain is not working, we dont want to drive
    // the robot at all!

    gyro.Reset();

    this->m_right.SetInverted(true);

    assert(&LBMotor != nullptr);
    assert(&LFMotor != nullptr);
    assert(&RBMotor != nullptr);
    assert(&RFMotor != nullptr);

    std::cout << "\tWPI_TalonFX\tOK" << std::endl;
    
    assert(&m_left != nullptr);
    assert(&m_right != nullptr);

    std::cout << "\tMotorGroup\tOK" << std::endl;

    CheckMotors();

}

void DriveSubsystem::Periodic()  {

    // Make sure our our motors are always OK, this helps
    // with electrical problems in the future because we will tell
    // which motors got unplugged!
    //CheckMotors();

    //frc::SmartDashboard::PutNumber("Watts", PD.GetTotalPower());


    frc::SmartDashboard::PutNumber("Gyro", this->GetHeading());
}

void DriveSubsystem::TankDrive(double left, double right) {
    m_drive.TankDrive(left, right);
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

double DriveSubsystem::SetLeftSpeed(double speed) {
    m_drive.Check();
    m_left.Set(speed);
}
double DriveSubsystem::SetRightSpeed(double speed){
    m_drive.Check();
    m_right.Set(speed);
}



void DriveSubsystem::ResetEncoders() {
    ZeroEncoderPos_Left = LFMotor.SetSelectedSensorPosition(1);
    ZeroEncoderPos_right= RFMotor.GetSelectedSensorPosition(1);

}
double DriveSubsystem::GetAverageEncoderDistance() {
    return (this->GetLeftEncoderPos() + this->GetRightEncoderPos()) / 2.0;
}

double DriveSubsystem::GetLeftEncoderPos() {
    return LFMotor.GetSensorCollection().GetIntegratedSensorPosition();
}
double DriveSubsystem::GetRightEncoderPos() {
    return -RFMotor.GetSensorCollection().GetIntegratedSensorPosition();
}

void DriveSubsystem::SetMaxSpeed(double speed) {
    m_drive.SetMaxOutput(speed);
}
double DriveSubsystem::GetHeading() {
    return gyro.GetAngle();
}

double DriveSubsystem::GetTurnRate() {
    // TODO
}
frc::Pose2d DriveSubsystem::GetPose() {
    // TODO
}

double DriveSubsystem::CalcualteDriveEncoder(double ft) {
    double Wheel_rotations = ft * this->WheelRPM_to_Distance_in_feet;
    double Motor_rotations = Wheel_rotations * this->GearBoxValue;
    double Encoder_rotations = Motor_rotations * this->EncoderPerRPM;


    return Encoder_rotations;
}

void DriveSubsystem::resetHeading() {
    this->gyro.Reset();
}

void DriveSubsystem::ToggleShift() {
    this->ShiftedState = !this->ShiftedState;

    this->left_piston.Set(this->ShiftedState);
    this->right_piston.Set(this->ShiftedState);

    frc::SmartDashboard::PutBoolean("Gear", this->ShiftedState);
}

bool DriveSubsystem::SetShift(bool shift) {
    this->left_piston.Set(shift);
    this->right_piston.Set(shift);

    frc::SmartDashboard::PutBoolean("Gear", shift);
}

//frc::DifferentialDriveWheelSpeeds DriveSubsystem::GetWheelSpeeds() {
    //frc::DifferentialDriveWheelSpeeds speed;
    //speed.left  = LFMotor.GetActiveTrajectoryVelocity(1) ;
    //speed.right = RFMotor.GetActiveTrajectoryVelocity(1);
//}
