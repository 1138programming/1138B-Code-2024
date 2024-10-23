#include "api.h"
#include "pros/optical.hpp"
#include "systems/classes.hpp"

inline pros::Motor intake1(5, pros::MotorGearset::blue);
inline pros::Optical ringColor(17);


inline Intake Intake(intake1, ringColor);
