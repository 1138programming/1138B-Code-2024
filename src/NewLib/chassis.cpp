#include <vector>
#include <cmath>
#include "api.h"
#include "chassis.h"
#include "functions.h"

// Private method to calculate ticks per inch based on wheel diameter, ticks per revolution, and gear ratio
double Chassis::calculateTickPerInch() {
    double wheelCircumference = wheelDiameter * M_PI;
    return (ticksPerRevolution * gearRatio) / wheelCircumference;
}

Chassis::Chassis(pros::MotorGroup& left, pros::MotorGroup& right, int imuPort, double wheelDiameterInches, double ratio, PID& drivePID, PID& turnPID)
    : leftMotors(left), rightMotors(right), imu(imuPort), wheelDiameter(wheelDiameterInches), ticksPerRevolution(360), gearRatio(ratio), drivePID(drivePID), turnPID(turnPID), pidTaskRunning(false) {
    tickPerInch = calculateTickPerInch();
}

double Chassis::getLeftPosition() {
    return (leftMotors.get_position(0));
}

double Chassis::getRightPosition() {
    return (rightMotors.get_position(0));
}

void Chassis::setDrivePID(double distance, int timeout) {
    // Set up the PID controller
    rightMotors.tare_position_all();
    leftMotors.tare_position_all();
    drivePID.setSetpoint(distance);

    // Start the PID task if it is not already running
    pidMutex.take(5); // Take the mutex with a timeout
    if (!pidTaskRunning) {
        pidTaskRunning = true;
        pros::Task pidTask(pidTaskFn, (void*)timeout, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT); // Start the task with 'this' as a parameter and pass the timeout value
    }
    pidMutex.give(); // Release the mutex
}

void Chassis::pidTaskFn(void* param) {
    Chassis* chassis = static_cast<Chassis*>(param);  // Correct cast
    int timeout_ms = reinterpret_cast<int>(param); // Retrieve the timeout value from the parameter
    // PID control loop
    while (true) {
        // Get the current process variable, typically the current sensor reading
        double leftCurrentPosition = chassis->getLeftPosition(); // You'll need to implement this
        double rightCurrentPosition = chassis->getRightPosition();
        // Update PID controller and clamp the output
        double rightPIDOutput = chassis->drivePID.update(rightCurrentPosition);
        double leftPIDOutput = chassis->drivePID.update(leftCurrentPosition);
    

        // Apply the PID output to your motors
        chassis->rightMotors.move(rightPIDOutput);
        chassis->leftMotors.move(leftPIDOutput);

        // Check exit conditions, for example, if the PID controller has converged
        if (chassis->drivePID.isConverged(10)) {  // Assuming isConverged is implemented
            break;
        }

        pros::delay(20); // Reasonable delay to prevent CPU hogging
    }

    // Indicate the PID task is done
    chassis->pidMutex.take(); // Safely update the shared flag
    chassis->pidTaskRunning = false;
    chassis->pidMutex.give(); // Release the mutex

}

void Chassis::waitUntilDone() {
    // Block until the PID task is no longer running
    while (true) {
        pidMutex.take(); // Take the mutex
        bool running = pidTaskRunning;
        pidMutex.give(); // Release the mutex

        if (!running) {
            break;  // Exit the loop if PID task is not running
        }

        pros::delay(20); // Delay to prevent hogging CPU
    }
}