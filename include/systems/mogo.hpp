#include "api.h"
#include "pros/adi.hpp"
#include "systems/classes.hpp"

inline pros::adi::Pneumatics clamp(8, false);
inline pros::adi::Pneumatics doinker(2, false);
inline Mogo MogoMech(clamp);