#include <chrono>
#include "pids.h"
#include "functions.h"
#include "regression.h"

PID::PID(double kp_, double ki_, double kd_, double slewRate_, Regression regression) :
    kp(kp_),
    ki(ki_),
    kd(kd_),
    slewRate(slewRate_),
    regression(regression),
    setpoint(0),
    integral(0),
    last_error(0), 
    last_output(0),
    initialized(false) {}

void PID::setSetpoint(double newSetpoint) {
    setpoint = newSetpoint;
}

double PID::update(double measured_value) {
    // Initialize time
    if (!initialized) {
        last_time = std::chrono::steady_clock::now();
        last_output = 0;
        initialized = true;
        return 0;
    }

    auto now = std::chrono::steady_clock::now();
    double dt = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_time).count() / 1000.0;

    if (dt <= 0) return 0;

    double error = setpoint - measured_value;
    integral += error * dt;
    double derivative = (error - last_error) / dt;
    // PID formula
    double output = kp * error + ki * integral + kd * derivative;

    double max_change = slewRate * dt;
        
    output = std::max(std::min(output, last_output + max_change), last_output - max_change);
    // Update for next call
    last_error = error;
    last_time = now;
    output = clamp(output, -127, 127);
    last_output = output;
    return output;
}

bool PID::isConverged(int timeout_ms) {
    // Assuming largeErrorRange, smallErrorRange, largeErrorTimeout,
    // and smallErrorTimeout are members of the PID class
    bool regressionExit = std::chrono::duration_cast<std::chrono::milliseconds>(
                             std::chrono::steady_clock::now() - last_time).count() >= regression.predict(std::abs(last_error));

    // You can define more exit conditions as needed
    bool timeoutExit = std::chrono::duration_cast<std::chrono::milliseconds>(
                             std::chrono::steady_clock::now() - last_time).count() >= timeout_ms;
    // Return true if any exit condition is met
    return regressionExit || timeoutExit;
}

