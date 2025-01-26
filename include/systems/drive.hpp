#pragma once
#include "api.h"
#include "lemlib/api.hpp"
#include "lemlib/chassis/trackingWheel.hpp"

// motors

inline pros::MotorGroup left_motors({20, -19, -18}, pros::MotorGearset::blue);
inline pros::MotorGroup right_motors({-16, 17, 21}, pros::MotorGearset::blue);

// sensors

inline pros::IMU imu(13);
inline pros::Rotation horzTracking(9);
 inline pros::Rotation vertTracking(8);

inline lemlib::TrackingWheel horzTracker(&horzTracking, lemlib::Omniwheel::NEW_2, 1.8125);
inline lemlib::TrackingWheel vertTracker(&vertTracking, lemlib::Omniwheel::NEW_2, 0);
// LEMLIB

inline double trackWidth = 11.5;
inline double WheelSize = 2.52;
inline int DriveRPM = 450;
inline int HorzDrift = 12;

// drivetrain settings

inline lemlib::Drivetrain drivetrain(
    &left_motors, // left motor group
    &right_motors, // right motor group
    trackWidth, // set the trackWidth variable to our LemLib track width
    WheelSize, // set the WheelSize variable to our LemLib wheel size
    DriveRPM, // set the DriveRPM variable to our LemLib RPM
    HorzDrift // set the HorzDrift variable to our horizontal drift tracking in LemLib
);

// tracking wheels


// odom settings

inline lemlib::OdomSensors OdomSensors(&vertTracker, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            &horzTracker, // horizontal tracking wheel 1
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
                                              10 // maximum acceleration (slew)
);

// Angular PID

inline lemlib::ControllerSettings angular_controller(3.5, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              30, // derivative gain (kD)
                                              5, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in millisecondsout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// Chassis Constructor

inline lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        OdomSensors // odometry sensors
);