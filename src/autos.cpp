#include "api.h"
#include "systems/drive.hpp"
#include "systems/mogo.hpp"
#include "systems/intake.hpp"
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

void soloAWP() {
    float startTime = pros::millis();
    chassis.setPose(52,-28,90);
    chassis.moveToPoint(29, -24, 2500, {.forwards=false, .maxSpeed=75});
    chassis.waitUntilDone();
    MogoMech.clamp();
    Intake.In();
    chassis.moveToPoint(24, -46, 2000, {.maxSpeed=127});
    chassis.waitUntilDone();
    chassis.moveToPose(60, -58, 135, 4000, {.horizontalDrift=12, .maxSpeed=127});
    Intake.In();
    // moveRelative(5, 75, 750);
    chassis.waitUntilDone();
    moveRelative(-5, 127, 750);
    chassis.waitUntilDone();
    chassis.moveToPoint(25, -5, 750);
    chassis.waitUntilDone();
    chassis.moveToPose(60, -58, 135, 2000, {.horizontalDrift=12, .maxSpeed=127});
    chassis.waitUntilDone();
    moveRelative(-5, 127, 750);
    chassis.waitUntilDone();
    chassis.moveToPoint(25, -5, 2500);
    Intake.Stop();
    chassis.waitUntilDone();
    float endTime = pros::millis();
    float totalTime = endTime - startTime;
    std::cout << totalTime << std::endl;
    master.print(0,0,"%f", totalTime);

}