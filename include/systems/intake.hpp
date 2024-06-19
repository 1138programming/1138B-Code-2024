#include "api.h"
#include "systems/classes.hpp"

inline pros::Motor intake1(-3, pros::MotorGearset::blue);
inline pros::Motor intake2(-8, pros::MotorGearset::blue);

inline Intake Intake(intake1, intake2);
