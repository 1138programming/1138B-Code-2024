#include "classes.hpp"
#include "lemlib/pid.hpp"
#include "pros/abstract_motor.hpp"

// motors
inline pros::Motor armMotor1(-11, pros::MotorGearset::green, pros::v5::MotorEncoderUnits::degrees);
inline pros::Motor armMotor2(12, pros::MotorGearset::green, pros::v5::MotorEncoderUnits::degrees);

//PID
inline lemlib::PID armPID(3,0,0);
//class definition
inline Arm arm(armMotor1, armMotor2, armPID, 0, 30, 112, 140, (12.0/60.0));