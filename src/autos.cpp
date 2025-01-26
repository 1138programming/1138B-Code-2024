#include "api.h"
#include "lemlib/chassis/chassis.hpp"
#include "pros/rtos.hpp"
#include "robodash/views/selector.hpp"
#include "systems/classes.hpp"
#include "systems/drive.hpp"
#include "robodash/api.h"
#include "systems/mogo.hpp"
#include "systems/intake.hpp"
#include "autos.hpp"
#include "systems/controlscheme.hpp"
#include "systems/arm.hpp"



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

void localAWPGoalRed() {
    chassis.setPose(-53.25,-24,270);
    moveRelative(-22, 50, 1500);
    chassis.waitUntilDone();
    MogoMech.clamp();
    pros::delay(250);
    Intake.In();
    chassis.turnToPoint(-24, -48, 1000);
    chassis.waitUntilDone();
    chassis.moveToPoint(-24, -48, 2000);
    chassis.waitUntilDone();
    chassis.moveToPose(-48, -10, 0, 2500);
    chassis.waitUntil(10);
    arm.setState(Arm::READY);
    intakeLift.extend();
    chassis.waitUntilDone();
    intakeLift.retract();
    pros::delay(250);
    moveRelative(-12, 127, 1000);
    chassis.waitUntilDone();
    chassis.moveToPoint(-54, 0, 1500);
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 1000);
    chassis.waitUntilDone();
    // chassis.moveToPoint(-55.5, 0, 1000);
    Intake.Stop();
    // chassis.waitUntilDone();
    arm.setState(Arm::ALLIANCESCORE);
    pros::delay(750);
    moveRelative(-6, 127, 1000);
    chassis.waitUntilDone();
    arm.setState(Arm::STOW);
    chassis.moveToPose(-66, -68, 180, 2500);
    chassis.waitUntil(6);
    Intake.In();
    chassis.waitUntilDone();
    moveRelative(-12, 127, 1000);
    chassis.waitUntilDone();
    Intake.Stop();
}
void localAWPGoalBlue() {
    // chassis.slew_drive_set(true);
    // chassis.slew_turn_set(true);
    chassis.setPose(60,-24,90);
    moveRelative(-32, 600, 1000);
    chassis.waitUntilDone();
    MogoMech.clamp();
    pros::delay(250);
    Intake.In();
    chassis.turnToPoint(28, -48, 750);
    chassis.waitUntilDone();
    chassis.moveToPoint(28, -48, 1500);
    chassis.waitUntilDone();
    pros::delay(500);
    // intakeLift.extend();
    chassis.moveToPoint(24, -6, 1500);
    chassis.waitUntilDone();
    Intake.Stop();
    // chassis.waitUntilDone();
    // arm.setState(Arm::READY);
    // intakeLift.retract();
    // while (ringColor.get_proximity() > 25) {

    // };
    // moveRelative(-6, 600, 1000);
    // chassis.waitUntilDone();
    // chassis.moveToPoint(-58.5, -3.5, 1500);
    // chassis.waitUntilDone();
    // chassis.turnToHeading(305, 1000);
    // chassis.waitUntilDone();
    // Intake.Stop();
    // arm.setState(Arm::ALLIANCESCORE);
}

void soloAWPFull() {
    chassis.setPose(-60, 18, 180);
    arm.setState(Arm::READY);
    Intake.In();
    chassis.moveToPoint(-60, 12, 750);
    chassis.waitUntilDone();
    chassis.turnToHeading(225, 750);
    chassis.waitUntilDone();
    Intake.Stop();
    arm.setState(Arm::ALLIANCESCORE);
    pros::delay(500);
    chassis.moveToPose(-28, 24, 270, 1500, {.forwards=false, .horizontalDrift=16});
    chassis.waitUntil(6);
    arm.setState(Arm::STOW);
    chassis.waitUntilDone();
    MogoMech.clamp();
    chassis.turnToPoint(-24, 44, 750);
    Intake.In();
    chassis.waitUntilDone();
    chassis.moveToPoint(-24, 44, 1000);
    chassis.waitUntilDone();
    chassis.moveToPose(-49, 7, 180, 2500);
    chassis.waitUntil(12);
    intakeLift.extend();
    chassis.waitUntilDone();
    intakeLift.retract();
    moveRelative(-6, 127, 750);
    chassis.waitUntilDone();
    chassis.moveToPoint(-48, -24, 1500);
    chassis.waitUntil(8);
    Intake.Stop();
    MogoMech.release();
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 750);
    chassis.waitUntilDone();
    chassis.moveToPoint(-31, -24, 1500, {.forwards=false, .earlyExitRange=3});
    Intake.Out();
    chassis.waitUntilDone();
    chassis.moveToPoint(-27, -24, 1000, {.maxSpeed=75});
    chassis.waitUntilDone();
    MogoMech.clamp();
    Intake.In();
    chassis.turnToPoint(-24, -44, 750);
    chassis.waitUntilDone();
    Intake.In();
    chassis.moveToPoint(-24, -44, 1000);
    chassis.waitUntilDone();
    arm.setState(Arm::SCORE);
    chassis.moveToPoint(-10, -12, 1250, {.forwards=false});
    chassis.waitUntil(8);
    Intake.Stop();
    chassis.waitUntilDone();
    arm.setState(Arm::READY);
}

void ringSideMiddle() {
    chassis.setPose(-60, 18, 180);
    arm.setState(Arm::READY);
    Intake.In();
    chassis.moveToPoint(-60, 12, 750);
    chassis.waitUntilDone();
    chassis.turnToHeading(225, 750);
    chassis.waitUntilDone();
    Intake.Stop();
    arm.setState(Arm::ALLIANCESCORE);
    pros::delay(500);
    chassis.moveToPose(-28, 24, 270, 1500, {.forwards=false, .horizontalDrift=16});
    chassis.waitUntil(6);
    arm.setState(Arm::STOW);
    chassis.waitUntilDone();
    MogoMech.clamp();
    chassis.turnToPoint(-6, 48, 750);
    chassis.waitUntilDone();
    Intake.In();
    chassis.moveToPose(-6, 48, 0, 2000);
    chassis.waitUntilDone();
    chassis.moveToPoint(-6, 55, 1500);
    chassis.waitUntilDone();
    chassis.moveToPoint(-24, 48, 1500);
    chassis.waitUntilDone();
    chassis.turnToPoint(-62, 62, 750);
    chassis.waitUntilDone();
    chassis.moveToPose(-63, 63, 315, 2000, {.horizontalDrift=20});
    chassis.waitUntilDone();
    chassis.tank(127, 127);
    while (ringColor.get_proximity() < 200) {};
    chassis.tank(0, 0);
    moveRelative(-6, 127, 750);
    chassis.waitUntilDone();
    chassis.turnToPoint(-48, 0, 750);
    chassis.waitUntilDone();
    chassis.moveToPose(-48, 7, 180, 1500);
    intakeLift.extend();
    chassis.waitUntilDone();
    intakeLift.retract();
    moveRelative(-6, 127, 750);
    chassis.waitUntilDone();

}

void pidTester() {
    chassis.setPose(0,0,0);
    chassis.moveToPoint(0, 24, 10000);
}