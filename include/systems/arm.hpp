#pragma once
#include "classes.hpp"
#include "LemLib/PID.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/motors.hpp"
#include <cstddef>

// motors
inline pros::Motor armMotor1(-14, pros::MotorGearset::green, pros::v5::MotorEncoderUnits::degrees);
inline pros::Motor armMotor2(12, pros::MotorGearset::green, pros::v5::MotorEncoderUnits::degrees);

//PID
inline lemlib::PID armPID(3,0,0);
//class definition
inline Arm arm(armMotor1, armMotor2, armPID, 0, 23, 60, 180, 140, 190, 200, 240, 255, (12.0/36.0));