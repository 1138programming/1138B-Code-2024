#include "classes.hpp"
#include "lemlib/pid.hpp"
#include "pros/abstract_motor.hpp"

// motors
inline pros::Motor armMotor(20, pros::MotorGearset::blue, pros::v5::MotorEncoderUnits::degrees);

//PID
inline lemlib::PID armPID(1,1,1);
//class definition
inline Arm arm(armMotor, armPID, 0, 0, 0, 0, (12.0/60.0));