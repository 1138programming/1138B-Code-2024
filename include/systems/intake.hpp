#include "api.h"
#include "pros/adi.hpp"
#include "pros/optical.hpp"
#include "systems/classes.hpp"

inline pros::Motor intake1(20, pros::MotorGearset::blue);
inline pros::Optical ringColor(17);
inline pros::adi::Pneumatics intakeLift(2, false);

inline Intake Intake(intake1, ringColor);
