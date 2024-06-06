#pragma once
#include "regression.h"
namespace BravoLib {
class PID {
private:
    double setpoint; // Desired value
    double integral; // Integral sum
    double last_error; // Last error value
    double last_output; // Last output value (for slew)
    Regression regression;
    float last_time; // Last time update was called

    bool initialized; // Whether the controller has been initialized

public:
    double kp; // Proportional gain
    double ki; // Integral gain
    double kd; // Derivative gain
    double slewRate; // Slew Rate for Movements
    PID(double kp_, double ki_, double kd_, double slewRate_, Regression regression);
    bool isConverged(int timeout_ms, float start_time);
    void setSetpoint(double newSetpoint);
    double update(double measured_value);
};
}