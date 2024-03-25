#pragma once
#include <chrono>
#include "regression.h"

class PID {
private:
    double setpoint; // Desired value
    double integral; // Integral sum
    double last_error; // Last error value
    double last_output; // Last output value (for slew)
    Regression regression;
    std::chrono::steady_clock::time_point last_time; // Last time update was called

    bool initialized; // Whether the controller has been initialized

public:
    double kp; // Proportional gain
    double ki; // Integral gain
    double kd; // Derivative gain
    double slewRate; // Slew Rate for Movements
    PID(double kp_, double ki_, double kd_, double slewRate_, Regression regression);
    bool isConverged(int timeout_ms);
    void setSetpoint(double newSetpoint);
    double update(double measured_value);
};