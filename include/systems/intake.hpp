#include "api.h"
#include "systems/classes.hpp"

inline pros::Motor intake1(5, pros::MotorGearset::blue);

inline Intake Intake(intake1);
