#include "api.h"
#include "pros/rtos.hpp"
#include "robodash/views/selector.hpp"
#include "systems/classes.hpp"
#include "systems/drive.hpp"
#include "robodash/api.h"
#include "systems/mogo.hpp"
#include "systems/intake.hpp"
#include "autos.hpp"
#include "systems/controlscheme.hpp"
#include "systems/doinker.hpp"



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

void relativeOdom(float xChange, float yChange, float maxSpeed, int timeout) {
    float currentX = chassis.getPose().x;
    float currentY = chassis.getPose().y;
    chassis.moveToPoint((currentX+xChange), (currentY+yChange), timeout);
}

void ringSideBlue() {
    float startTime = pros::millis();
    chassis.setPose(52,28,90);
    chassis.moveToPoint(28, 24, 2500, {.forwards=false, .maxSpeed=75});
    chassis.waitUntilDone();
    MogoMech.clamp();
    Intake.In();
    chassis.moveToPoint(29, 52, 1500, {.maxSpeed=600});
    chassis.waitUntilDone();
    chassis.moveToPoint(10, 52, 1000);
    chassis.waitUntilDone();
    float endTime = pros::millis();
    float totalTime = endTime - startTime;
    std::cout << totalTime << std::endl;
    master.print(0,0,"%f", totalTime);
}

void goalSideBlue() {
    float startTime = pros::millis();
    ringColor.set_led_pwm(100);
    chassis.setPose(52,-24, 90);
    moveRelative(-24, 450, 1500);
    chassis.waitUntilDone();
    MogoMech.clamp();
    Intake.In();
    chassis.turnToPoint(24, -52, 750);
    chassis.waitUntilDone();
    chassis.moveToPoint(24, -46, 1000);
    chassis.waitUntilDone();
    while (ringColor.get_proximity() > 25) {
        pros::delay(1);
        master.print(1, 1, "waiting");
    }
    master.print(1, 1, "wait done");
    moveRelative(-6, 600, 750);
    chassis.waitUntilDone();
    Intake.Stop();
    chassis.moveToPoint(28, -6, 1500);
    chassis.waitUntilDone();
}

void goalSideRed() {
    float startTime = pros::millis();
    ringColor.set_led_pwm(100);
    chassis.setPose(-52,-24, 270);
    moveRelative(-24, 450, 1500);
    chassis.waitUntilDone();
    MogoMech.clamp();
    Intake.In();
    chassis.turnToPoint(-24, -52, 750);
    chassis.waitUntilDone();
    chassis.moveToPoint(-24, -46, 1000);
    chassis.waitUntilDone();
    while (ringColor.get_proximity() > 25) {
        pros::delay(1);
        master.print(1, 1, "waiting");
    }
    master.print(1, 1, "wait done");
    moveRelative(-6, 600, 750);
    chassis.waitUntilDone();
    Intake.Stop();
    chassis.moveToPoint(-28, -6, 1500);
    chassis.waitUntilDone();
}

void soloAwpBlue() {
    float startTime = pros::millis();
    chassis.setPose(55, -56, 90);
    // chassis.moveToPoint(24, -60, 1000, {.forwards=false, .earlyExitRange=6});
    // chassis.waitUntilDone();
    chassis.moveToPose(0, -48, 120, 5000, {.forwards=false, .horizontalDrift=10});
    /*
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
    chassis.moveToPoint(64, -60, 4000, {.maxSpeed=75});
    chassis.waitUntilDone();
    moveRelative(-6, 127, 750);
    chassis.waitUntilDone();
    chassis.moveToPoint(25, -5, 2500);
    chassis.waitUntil(2);
    Intake.Out();
    chassis.waitUntilDone();
    Intake.Stop();
    */
    float endTime = pros::millis();
    float totalTime = endTime - startTime;
    std::cout << totalTime << std::endl;
    master.print(0,0,"%f", totalTime);

}