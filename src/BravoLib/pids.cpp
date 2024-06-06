#include "BravoLib/pids.h"
#include "BravoLib/utils.h"
#include "BravoLib/regression.h"
#include "pros/rtos.hpp"

namespace BravoLib {

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
        last_time = pros::millis();
        last_output = 0;
        initialized = true;
        return 0;
    }

    float ct = pros::millis();
    double dt = (ct - last_time) / 1000.0;

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
    last_time = ct;
    output = clamp(output, -127, 127);
    last_output = output;
    return output;
}

bool PID::isConverged(int timeout_ms, float start_time) {
    //compare against all possible exit timeouts using a linear regression algorithm
    bool regressionExit = pros::millis() - last_time >= regression.predict(std::abs(last_error));

    // compare the overall time the pid loop has taken more time that the timeout allows
    bool timeoutExit = start_time - pros::millis() >= timeout_ms;
    // Return true if any exit condition is met
    return regressionExit || timeoutExit;
}

}