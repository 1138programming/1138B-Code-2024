#include "api.h"
#include "pros/adi.hpp"
#include "systems/classes.hpp"

inline pros::adi::Pneumatics clamp(8, false);
inline Mogo MogoMech(clamp);