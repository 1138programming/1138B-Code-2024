#include "api.h"
#include "pros/adi.hpp"
#include "pros/optical.hpp"
#include "systems/classes.hpp"

inline pros::Motor intake1(5, pros::MotorGearset::blue);
inline pros::Optical ringColor(17);

inline pros::adi::Pneumatics intakePiston(3, false);

inline Intake Intake(intake1, ringColor);
