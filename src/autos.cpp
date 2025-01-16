#include "api.h"
#include "lemlib/chassis/chassis.hpp"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "robodash/views/selector.hpp"
#include "systems/classes.hpp"
#include "systems/drive.hpp"
#include "robodash/api.h"
#include "systems/mogo.hpp"
#include "systems/intake.hpp"
#include "systems/doinker.hpp"
#include "autos.hpp"
#include "systems/controlscheme.hpp"
#include "systems/arm.hpp"


/**
* @brief Move the robot a relative distance forwards or backwards
*
* @param distance distance to be moved
* @param timeout the timeout duration for the movement
*/
void moveRelative(float distance, float minSpeed, int timeout) {
    double headingRadians = chassis.getPose(true).theta;
    double startingX = chassis.getPose().x;
    double startingY = chassis.getPose().y;
    double deltaX = distance * sin(headingRadians);
    double deltaY = distance * cos(headingRadians);
    double newX = startingX + deltaX;
    double newY = startingY + deltaY;
    if (distance > 0) {
        chassis.moveToPoint(newX, newY, timeout, {.forwards=true, .minSpeed=minSpeed});
    }
    else if (distance < 0) {
        chassis.moveToPoint(newX, newY, timeout, {.forwards=false, .minSpeed=minSpeed});
    }
};

void relativeOdom(float xChange, float yChange, float maxSpeed, int timeout) {
    float currentX = chassis.getPose().x;
    float currentY = chassis.getPose().y;
    chassis.moveToPoint((currentX+xChange), (currentY+yChange), timeout);
}

void goalRushAWP() {
    chassis.setPose(-51, -61, 90);
    chassis.moveToPoint(-20, -61, 750);
    arm.setState(Arm::READY);
    Intake.In();
    chassis.waitUntilDone();
    chassis.moveToPoint(-18, -55, 1500);
    chassis.waitUntil(3);
    Intake.Stop();
    arm.setState(Arm::MOGOSCORE);
    chassis.waitUntilDone();
    moveRelative(6, 0, 500);
    chassis.waitUntilDone();
    chassis.turnToHeading(330, 1000);
    chassis.waitUntilDone();
    arm.setState(Arm::STOW);
    chassis.turnToPoint(-28, -50, 750);
    chassis.waitUntilDone();
    Intake.In();
    chassis.moveToPoint(-28, -50, 750);
    pros::delay(500);
    Intake.Stop();
    chassis.waitUntilDone();
    chassis.turnToPoint(-32, -20, 750);
    chassis.waitUntilDone();
    chassis.moveToPoint(-32, -20, 1000, {.forwards=false});
    chassis.waitUntilDone();
    MogoMech.clamp();
    Intake.In();
}

void crossFieldSoloAWP() {
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.setPose(-57, 16, 180);
    arm.setState(Arm::READY);
    Intake.In();
    moveRelative(6, 0, 750);
    chassis.waitUntilDone();
    chassis.turnToPoint(-72, 0, 750);
    chassis.waitUntilDone();
    Intake.Stop();
    arm.setState(Arm::SCORE);
    pros::delay(1000);
    moveRelative(-4, 0, 750);
    chassis.waitUntilDone();
    std::cout << chassis.getPose().x << std::endl;
    std::cout << chassis.getPose().y << std::endl;
    std::cout << chassis.getPose().theta << std::endl;
    arm.setState(Arm::STOW);
    chassis.moveToPoint(-33, 20, 1250, {.forwards=false});
    chassis.waitUntilDone();
    MogoMech.clamp();
}