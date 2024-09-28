#include "api.h"
#include "systems/classes.hpp"

inline pros::Motor intake1(-18, pros::MotorGearset::blue);
inline pros::Motor intake2(13, pros::MotorGearset::blue);

inline Intake Intake(intake1, intake2);
