#ifndef CHASSIS_H
#define CHASSIS_H
#pragma once
#include <vector>
#include <cmath>
#include "api.h" // Ensure this includes definition for pros::MotorGroup, pros::Mutex, etc.
#include "pids.h"

class Chassis {
private:
    pros::MotorGroup& leftMotors;
    pros::MotorGroup& rightMotors;
    PID& drivePID;
    PID& turnPID;
    pros::Mutex pidMutex;
    bool pidTaskRunning;
    pros::Imu imu;
    double wheelDiameter;
    double ticksPerRevolution;
    double gearRatio;
    double tickPerInch;
    double calculateTickPerInch();

public:
    Chassis(pros::MotorGroup& left, pros::MotorGroup& right, int imuPort, double wheelDiameterInches, double ratio, PID& drivePID, PID& turnPID);
    double getLeftPosition();
    double getRightPosition();
    void setDrivePID(double distance, int timeout);
    static void pidTaskFn(void* param);
    void waitUntilDone();

    // Additional methods...
};

#endif // CHASSIS_H
