#include "api.h"

// controllers

inline pros::Controller master(pros::E_CONTROLLER_MASTER);

void driveControl(void* param);
void intakeControl(void* param);
void mogoControl(void* param);
void doinkerControl(void* param);
void armControl(void* param);