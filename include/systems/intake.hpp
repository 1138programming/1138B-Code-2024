#include "api.h"
#include "systems/classes.hpp"

inline pros::Motor intake1(20, pros::MotorGearset::blue);
inline pros::Motor intake2(-11, pros::MotorGearset::blue);

inline Intake Intake(intake1, intake2);
