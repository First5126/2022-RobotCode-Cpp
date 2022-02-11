#pragma once

#include <frc/smartdashboard/SmartDashboard.h>

namespace RobotMode {
    enum mode {
        AUTO = 0,
        TELEOP,
        DISABLED,
        TEST
    };
}

class Layer {
    public:

        Layer();
        ~Layer();

        const static int test = 0;

        // Values Layer Contains

        // Robot Forward Drive Speed
        double forward_drive_speed = 0;

        // Robot Turning Drive Speed
        double turning_drive_speed = 0;

        // Sets the left motor to lock
        bool left_locked = false;

        // Sets the right motor to lock
        bool right_locked = false;

        // Pi Yaw [-30, 30] The yaw of the ball from the robot
        double pi_yaw = 0;

        // Pi Pitch [-30, 30] The pitch of the ball from the robot
        double pi_pitch = 0;

        // Pi Mode [-1, 2] The mode of the pi (DRIVER, BLUEBALL, REDBALL, TAPE)
        int pi_mode = 0;

        // Pi Driver Mode [true, false] Whether the pi is in driver mode or not
        bool pi_driver_mode = false;

        // Pi Active [true, false] Whether the pi is active or not (latency > 0)
        bool pi_active = false;

        // Color Sensor red value
        int cs_r = 0;

        // Color Sensor green value
        int cs_g = 0;

        // Color Sensor blue value
        int cs_b = 0;

        // If the user wants to use the auto or not
        bool GrabBall = false;

        void OutputToSmartdashboard();

    
};