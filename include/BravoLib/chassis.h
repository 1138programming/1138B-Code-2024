#ifndef CHASSIS_H
#define CHASSIS_H
#pragma once
#include "pros/motor_group.hpp"
#include "pros/imu.hpp"
#include "pids.h"
namespace BravoLib {

class Chassis {
private:
    pros::MotorGroup& leftMotors;
    pros::MotorGroup& rightMotors;
    PID& drivePID;
    PID& turnPID;
    pros::Mutex pidMutex;
    int imuPort;
    bool pidTaskRunning;
    double wheelDiameter;
    double ticksPerRevolution;
    double drivingGear;
    double drivenGear;
    double tickPerInch;
    double calculateTickPerInch();

public:
    Chassis(pros::MotorGroup& left, pros::MotorGroup& right, int imuPort, double wheelDiameterInches, double drivingGear, double drivenGear, PID& drivePID, PID& turnPID);
    pros::Imu imu;
    void calibrate(); 
    double getLeftPosition();
    double getRightPosition();
    void setDrivePID(double distance, int timeout);
    void setTurnPID(double distance, int timeout);
    static void DrivePIDTaskFn(void* param);
    static void TurnPIDTaskFn(void* param);
    void waitUntilDone();

    // Additional methods...
};
}
#endif // CHASSIS_H
