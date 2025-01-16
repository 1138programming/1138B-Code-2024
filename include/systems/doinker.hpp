#include "pros/adi.hpp"
#include "systems/classes.hpp"

inline pros::adi::Pneumatics leftDoinkerPiston(2, false);

inline Doinker leftDoinker(leftDoinkerPiston);

inline pros::adi::Pneumatics rightDoinkerPiston(4, false);

inline Doinker rightDoinker(rightDoinkerPiston);
