#include "api.h"
#include "systems/classes.hpp"

inline pros::adi::Pneumatics clamp(1, false);
inline pros::adi::Pneumatics tilt(2, false);

inline Mogo MogoMech(clamp, tilt);