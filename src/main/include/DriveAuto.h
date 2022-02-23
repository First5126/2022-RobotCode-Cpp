#pragma once

#include "Layer.h"
#include <frc/Filesystem.h>
#include <frc/trajectory/TrajectoryUtil.h>
#include <wpi/fs.h>
#include <frc/Encoder.h>

#include "DriveAutoConst.h"
#include <frc/drive/DifferentialDrive.h>

#include <frc/kinematics/DifferentialDriveOdometry.h>
#include <frc/ADXRS450_Gyro.h>


namespace Auto {
    class DriveSubsystem {
        public:

        DriveSubsystem(Layer *layer);
        ~DriveSubsystem();

        void Periodic();


        /**
         * Drives the robot using arcade controls.
         *
         * @param fwd the commanded forward movement
         * @param rot the commanded rotation
         */
        void ArcadeDrive(double fwd, double rot);

        /**
         * Controls each side of the drive directly with a voltage.
         *
         * @param left the commanded left output
         * @param right the commanded right output
         */
        void TankDriveVolts(units::volt_t left, units::volt_t right);

        /**
         * Resets the drive encoders to currently read a position of 0.
         */
        void ResetEncoders();

        /**
         * Gets the average distance of the TWO encoders.
         *
         * @return the average of the TWO encoder readings
         */
        double GetAverageEncoderDistance();

        /**
         * Gets the left drive encoder.
         *
         * @return the left drive encoder
         */
        frc::Encoder& GetLeftEncoder();

        /**
         * Gets the right drive encoder.
         *
         * @return the right drive encoder
         */
        frc::Encoder& GetRightEncoder();

        /**
         * Sets the max output of the drive.  Useful for scaling the drive to drive
         * more slowly.
         *
         * @param maxOutput the maximum output to which the drive will be constrained
         */
        void SetMaxOutput(double maxOutput);

        /**
         * Returns the heading of the robot.
         *
         * @return the robot's heading in degrees, from -180 to 180
         */
        units::degree_t GetHeading() const;

        /**
         * Returns the turn rate of the robot.
         *
         * @return The turn rate of the robot, in degrees per second
         */
        double GetTurnRate();

        /**
         * Returns the currently-estimated pose of the robot.
         *
         * @return The pose.
         */
        frc::Pose2d GetPose();

        /**
         * Returns the current wheel speeds of the robot.
         *
         * @return The current wheel speeds.
         */
        frc::DifferentialDriveWheelSpeeds GetWheelSpeeds();

        /**
         * Resets the odometry to the specified pose.
         *
         * @param pose The pose to which to set the odometry.
         */
        void ResetOdometry(frc::Pose2d pose);

        private:

        frc::DifferentialDriveOdometry m_odometry {};

        // The robot's drive
        Layer * m_layer;

        // The left-side drive encoder
        frc::Encoder m_leftEncoder {};

        // The right-side drive encoder
        frc::Encoder m_rightEncoder {};

        // The gyro sensor
        frc::ADXRS450_Gyro m_gyro;

        
    };

    class DriveAuto {
        private:

        Layer *m_layer;
        
        //PathPlannerTrajectory examplePath;
        //PathPlannerTrajectory::PathPlannerState exampleState;

        

    
        
        public:

        DriveAuto(Layer *layer);
        ~DriveAuto();

        void update();
    }; 
}