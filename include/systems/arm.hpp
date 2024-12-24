#include "classes.hpp"
#include "lemlib/pid.hpp"
#include "pros/abstract_motor.hpp"

// motors
inline pros::Motor armMotor1(-14, pros::MotorGearset::red, pros::v5::MotorEncoderUnits::degrees);

//PID
inline lemlib::PID armPID(3,0,0);
//class definition
inline Arm arm(armMotor1, armPID, 0, 50, 160, 200, 240, 255, (36.0/36.0));