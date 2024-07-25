#include "api.h"
#include "systems/classes.hpp"

inline pros::Motor intake1(-9, pros::MotorGearset::blue);
inline pros::Motor intake2(-1, pros::MotorGearset::blue);

inline Intake Intake(intake1, intake2);
