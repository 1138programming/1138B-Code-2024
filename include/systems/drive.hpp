#pragma once
#include "api.h"
#include "lemlib/api.hpp"

// motors
inline pros::MotorGroup left_motors({-7, -19, 20}, pros::MotorGearset::blue); // left drive motor group
inline pros::MotorGroup right_motors({6, -11, 12}, pros::MotorGearset::blue); // right drive motor group

// sensors
inline pros::IMU imu(20); // define our imu

// LemLib
inline int trackWidth = 10; // distance between our left and right wheels
inline int WheelSize = lemlib::Omniwheel::NEW_325; // drivetrain wheel size
inline int DriveRPM = 400; // drivetrain RPM
inline int HorzDrift = 12; // the maximum lateral speed before we drift sideways

// drivetrain definition
inline lemlib::Drivetrain drivetrain(
    &left_motors, // left motor group
    &right_motors, // right motor group
    trackWidth, // set the trackWidth variable to our LemLib track width
    WheelSize, // set the WheelSize variable to our LemLib wheel size
    DriveRPM, // set the DriveRPM variable to our LemLib RPM
    HorzDrift // set the HorzDrift variable to our horizontal drift tracking in LemLib
);


// odom settings
inline lemlib::OdomSensors OdomSensors(nullptr, // vertical tracking wheel 1, set to nullptr as we are using IMEs
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// PIDs

// Lateral PID

inline lemlib::ControllerSettings lateral_controller(10, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              3, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// Angular PID

inline lemlib::ControllerSettings angular_controller(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// Chassis Constructor

inline lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        OdomSensors // odometry sensors
);