#include "api.h"

// controllers

inline pros::Controller master(pros::E_CONTROLLER_MASTER);

void driveControl();
void intakeControl(void* param);
void mogoControl();
void doinkerControl();
void armControl(void* param);