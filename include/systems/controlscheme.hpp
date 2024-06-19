#include "api.h"
#include "pros/misc.h"

// controllers

inline pros::Controller master(pros::E_CONTROLLER_MASTER);

void driveControl();
void intakeControl();
void mogoControl();