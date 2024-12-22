#include "classes.hpp"
#include "lemlib/pid.hpp"
#include "pros/abstract_motor.hpp"

// motors
inline pros::Motor armMotor1(-11, pros::MotorGearset::green, pros::v5::MotorEncoderUnits::degrees);

//PID
inline lemlib::PID armPID(3,0,0);
//class definition
inline Arm arm(armMotor1, armPID, 0, 34, 112, 145, (24.0/36.0));