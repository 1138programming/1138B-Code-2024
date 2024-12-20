#include "api.h"
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



/**
* @brief Move the robot a relative distance forwards or backwards
*
* @param distance distance to be moved
* @param timeout the timeout duration for the movement
*/
void moveRelative(float distance, float maxSpeed, int timeout) {
    double headingRadians = chassis.getPose(true).theta;
    double startingX = chassis.getPose().x;
    double startingY = chassis.getPose().y;
    double deltaX = distance * sin(headingRadians);
    double deltaY = distance * cos(headingRadians);
    double newX = startingX + deltaX;
    double newY = startingY + deltaY;
    if (distance > 0) {
        chassis.moveToPoint(newX, newY, timeout, {.forwards=true, .maxSpeed=maxSpeed});
    }
    else if (distance < 0) {
        chassis.moveToPoint(newX, newY, timeout, {.forwards=false, .maxSpeed=maxSpeed});
    }
};


void ringSideBlue() {
    float startTime = pros::millis();
    chassis.setPose(52,28,90);
    chassis.moveToPoint(28, 24, 2500, {.forwards=false, .maxSpeed=75});
    chassis.waitUntilDone();
    MogoMech.clamp();
    Intake.In();
    chassis.turnToPoint(20, 52, 750);
    chassis.waitUntilDone();
    chassis.moveToPoint(29, 52, 1500);
    chassis.waitUntilDone();
    chassis.moveToPoint(11, 52, 1000);
    chassis.waitUntilDone();
    pros::delay(500);
    chassis.moveToPoint(10, 41, 1000);
    chassis.waitUntilDone();
    chassis.turnToPoint(38, 24, 750);
    chassis.waitUntilDone();
    chassis.moveToPose(36, 14, 180, 2500, {.horizontalDrift=12});
    chassis.waitUntilDone();
    stackDoinker.down();
    moveRelative(-10, 127, 1500);
    chassis.waitUntilDone();
    stackDoinker.up();
    chassis.moveToPoint(48, 6, 750);
    chassis.waitUntilDone();
    chassis.moveToPoint(25, 5, 2500);
    Intake.Stop();
    float endTime = pros::millis();
    float totalTime = endTime - startTime;
    std::cout << totalTime << std::endl;
    master.print(0,0,"%f", totalTime);
}

void soloAwpBlue() {
    float startTime = pros::millis();
    chassis.setPose(52, -60, 90);
    // chassis.moveToPoint(24, -60, 1000, {.forwards=false, .earlyExitRange=6});
    // chassis.waitUntilDone();
    chassis.moveToPose(8, -52, 120, 5000, {.forwards=false, .horizontalDrift=10});
    chassis.waitUntilDone();
    MogoMech.clamp();
    Intake.In();
    chassis.moveToPoint(18, -49, 1250, {.minSpeed=50});
    chassis.waitUntilDone();
    pros::delay(750);
    MogoMech.release();
    chassis.waitUntilDone();
    chassis.moveToPoint(24, -30, 2000, {.forwards=false});
    chassis.waitUntilDone();
    MogoMech.clamp();
    chassis.moveToPoint(58, -24, 750, {.forwards=false});
    chassis.waitUntilDone();
    chassis.turnToPoint(64, -60, 750);
    chassis.waitUntilDone();
    Intake.setFloatingSpeed(300);
    Intake.setFlipperSpeed(300);
    chassis.moveToPoint(64, -60, 4000, {.maxSpeed=75});
    chassis.waitUntilDone();
    moveRelative(-6, 127, 750);
    chassis.waitUntilDone();
    Intake.setFlipperSpeed(600);
    Intake.setFloatingSpeed(600);
    chassis.moveToPoint(25, -5, 2500);
    chassis.waitUntil(2);
    Intake.Out();
    chassis.waitUntilDone();
    Intake.Stop();
    float endTime = pros::millis();
    float totalTime = endTime - startTime;
    std::cout << totalTime << std::endl;
    master.print(0,0,"%f", totalTime);
}

void soloAwpRed() {
    float startTime = pros::millis();
    chassis.setPose(-55.5, -58.5, 270);
    // chassis.moveToPoint(24, -60, 1000, {.forwards=false, .earlyExitRange=6});
    // chassis.waitUntilDone();
    chassis.moveToPose(-10, -51, 235, 2750, {.forwards=false, .horizontalDrift=10});
    chassis.waitUntilDone();
    MogoMech.clamp();
    Intake.In();
    chassis.moveToPoint(-25, -49, 1250, {.minSpeed=50});
    chassis.waitUntilDone();
    pros::delay(750);
    MogoMech.release();
    chassis.waitUntilDone();
    chassis.moveToPoint(-25, -30, 2000, {.forwards=false});
    chassis.waitUntilDone();
    MogoMech.clamp();
    chassis.moveToPoint(-58, -24, 750, {.forwards=false});
    chassis.waitUntilDone();
    chassis.turnToPoint(-64, -60, 750);
    chassis.waitUntilDone();
    Intake.setFloatingSpeed(300);
    Intake.setFlipperSpeed(300);
    chassis.moveToPoint(-64, -60, 4000, {.maxSpeed=75});
    chassis.waitUntilDone();
    moveRelative(-6, 127, 750);
    chassis.waitUntilDone();
    Intake.setFlipperSpeed(600);
    Intake.setFloatingSpeed(600);
    chassis.moveToPoint(-25, -5, 2500, {.maxSpeed=75});
    chassis.waitUntil(2);
    Intake.Out();
    chassis.waitUntilDone();
    Intake.Stop();
    float endTime = pros::millis();
    float totalTime = endTime - startTime;
    std::cout << totalTime << std::endl;
    master.print(0,0,"%f", totalTime);
}