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
#include "systems/doinker.hpp"
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

void driveBack() {
    moveRelative(-8, 600, 1000);
    chassis.waitUntilDone();
}

void ringSideRedOld() {
    float startTime = pros::millis();
    chassis.setPose(-52,24,270);
    moveRelative(-24, 450, 1500);
    chassis.waitUntilDone();
    MogoMech.clamp();
    Intake.In();
    chassis.turnToPoint(-26, 42, 750);
    chassis.waitUntilDone();
    chassis.moveToPoint(-26, 42, 1500);
    chassis.waitUntilDone();
    while (ringColor.get_proximity() > 25) {
        pros::delay(1);
        master.print(1, 1, "waiting");
    }
    master.print(1, 1, "wait done");
    chassis.moveToPoint(-18, 40, 1500);
    chassis.waitUntilDone();
    while (ringColor.get_proximity() > 25) {
        pros::delay(1);
        master.print(1, 1, "waiting");
    }
    master.print(1, 1, "wait done");
    moveRelative(-32, 600, 1250);
    chassis.waitUntilDone();
    Intake.Out();
    chassis.turnToPoint(-54, -54, 750);
    chassis.waitUntilDone();
    chassis.moveToPoint(-54, -54, 1500);
    chassis.waitUntilDone();
    Intake.Stop();
    float endTime = pros::millis();
    float totalTime = endTime - startTime;
    std::cout << totalTime << std::endl;
    master.print(0,0,"%f", totalTime);
}

void ringSideRed() {
    ringColor.set_led_pwm(100);
    float startTime = pros::millis();
    chassis.setPose(-52,24,270);
    moveRelative(-20, 450, 1750);
    chassis.waitUntilDone();
    MogoMech.clamp();
    Intake.In();
    chassis.turnToPoint(-26, 42, 750);
    chassis.waitUntilDone();
    chassis.moveToPoint(-26, 42, 1250);
    chassis.waitUntilDone();
    while (ringColor.get_proximity() > 25) {
        pros::delay(1);
        master.print(1, 1, "waiting");
    }
    master.print(1, 1, "wait done");
    chassis.moveToPose(-20, 46, 90, 1250, {.horizontalDrift=30});
    chassis.waitUntilDone();
    while (ringColor.get_proximity() > 25) {
        pros::delay(1);
        master.print(1, 1, "waiting");
    }
    master.print(1, 1, "wait done");
    moveRelative(-18, 600, 1250);
    chassis.waitUntilDone();
    chassis.moveToPose(-19, 38, 90, 1750, {.horizontalDrift=30});
    chassis.waitUntilDone();
    while (ringColor.get_proximity() > 20) {
        pros::delay(1);
        master.print(1, 1, "waiting");
    }
    master.print(1, 1, "wait done");
    moveRelative(-12, 600, 1000);
    chassis.waitUntilDone();
    chassis.turnToPoint(-46, 9, 750);
    chassis.moveToPoint(-46, 9, 1500);
    chassis.waitUntil(6);
    Intake.Stop();
    intakePiston.extend();
    chassis.waitUntilDone();
    Intake.In();
    intakePiston.retract();
    pros::delay(500);
    moveRelative(-12, 600, 1000);
    //moveRelative(-12, 600, 1250);
    float endTime = pros::millis();
    float totalTime = endTime - startTime;
    std::cout << totalTime << std::endl;
    master.print(0,0,"%f", totalTime);
}

void ringSideBlueOld() {
    float startTime = pros::millis();
    chassis.setPose(52,24,90);
    moveRelative(-24, 450, 1500);
    chassis.waitUntilDone();
    MogoMech.clamp();
    Intake.In();
    chassis.turnToPoint(26, 42, 750);
    chassis.waitUntilDone();
    chassis.moveToPoint(26, 42, 1500);
    chassis.waitUntilDone();
    while (ringColor.get_proximity() > 25) {
        pros::delay(1);
        master.print(1, 1, "waiting");
    }
    master.print(1, 1, "wait done");
    chassis.moveToPoint(18, 40, 1250);
    chassis.waitUntilDone();
    while (ringColor.get_proximity() > 25) {
        pros::delay(1);
        master.print(1, 1, "waiting");
    }
    master.print(1, 1, "wait done");
    moveRelative(-32, 600, 1250);
    chassis.waitUntilDone();
    chassis.turnToPoint(50, -50, 750);
    chassis.waitUntilDone();
    chassis.moveToPoint(50, -50, 1500);
    chassis.waitUntilDone();
    Intake.Stop();
    float endTime = pros::millis();
    float totalTime = endTime - startTime;
    std::cout << totalTime << std::endl;
    master.print(0,0,"%f", totalTime);
}

void ringSideBlue() {
    ringColor.set_led_pwm(100);
    float startTime = pros::millis();
    chassis.setPose(52,24,90);
    moveRelative(-20, 450, 1750);
    chassis.waitUntilDone();
    MogoMech.clamp();
    Intake.In();
    chassis.turnToPoint(26, 46, 750);
    chassis.waitUntilDone();
    chassis.moveToPoint(26, 46, 1250);
    chassis.waitUntilDone();
    while (ringColor.get_proximity() > 25) {
        pros::delay(1);
        master.print(1, 1, "waiting");
    }
    master.print(1, 1, "wait done");
    chassis.moveToPose(18, 46, 270, 1250, {.horizontalDrift=30});
    chassis.waitUntilDone();
    while (ringColor.get_proximity() > 25) {
        pros::delay(1);
        master.print(1, 1, "waiting");
    }
    master.print(1, 1, "wait done");
    moveRelative(-18, 600, 1250);
    chassis.waitUntilDone();
    chassis.moveToPose(17, 42, 270, 2000, {.horizontalDrift=30});
    chassis.waitUntilDone();
    while (ringColor.get_proximity() > 20) {
        pros::delay(1);
        master.print(1, 1, "waiting");
    }
    master.print(1, 1, "wait done");
    moveRelative(-12, 600, 1000);
    chassis.moveToPoint(63, 64, 2250);
    chassis.waitUntilDone();
    moveRelative(-18, 600, 1000);
    chassis.waitUntilDone();
    Intake.Stop();
    chassis.turnToPoint(28, 6, 750);
    chassis.waitUntilDone();
    chassis.moveToPoint(28, 6, 1250);
    //moveRelative(-12, 600, 1250);
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
    chassis.moveToPoint(28, -6, 1500);
    chassis.waitUntilDone();
    Intake.Stop();
}

void soloAWPBlue() {
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
    Intake.Stop();
    float endTime = pros::millis();
    float totalTime = endTime - startTime;
    std::cout << totalTime << std::endl;
    master.print(0,0,"%f", totalTime);
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
    chassis.moveToPoint(-24, -42, 1250);
    chassis.waitUntilDone();
    // pros::delay(0);
    moveRelative(-6, 600, 750);
    chassis.waitUntilDone();
    Intake.Stop();
    chassis.moveToPoint(-24, -4, 3000);
    chassis.waitUntilDone();
}

void goalSideRedElims() {
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
    MogoMech.release();
    chassis.waitUntilDone();
    chassis.turnToHeading(95, 650);
    chassis.waitUntilDone();
    moveRelative(7, 600, 1000);
    chassis.waitUntilDone();
    stackDoinker.down();
    chassis.moveToPoint(chassis.getPose().x-20, chassis.getPose().y-16, 1500, {.forwards=false});
    chassis.waitUntilDone();
}

void goalSideAWPRed() {
    float startTime = pros::millis();
    ringColor.set_led_pwm(100);
    chassis.setPose(-52,-24, 270);
    moveRelative(-20, 450, 1500);
    chassis.waitUntilDone();
    MogoMech.clamp();
    Intake.In();
    chassis.turnToPoint(-24, -46, 750);
    chassis.waitUntilDone();
    chassis.moveToPoint(-24, -44, 1000);
    chassis.waitUntilDone();
    while (ringColor.get_proximity() > 25) {
        pros::delay(1);
        master.print(1, 1, "waiting");
    }
    master.print(1, 1, "wait done");
    // moveRelative(-6, 600, 750);
    // chassis.waitUntilDone();
    chassis.moveToPoint(-55, -32, 1250, {.forwards=false});
    chassis.waitUntilDone();
    Intake.Stop();
    MogoMech.release();
    Intake.setSpeed(250);
    chassis.moveToPose(-44, 5, 0, 2500, {.horizontalDrift=18});
    Intake.In();
    chassis.waitUntilDone();
    while (!(ringColor.get_hue() > 350 || ringColor.get_hue() < 20) && ringColor.get_proximity() > 50) {
        pros::delay(1);
        master.print(1, 0, "waiting");
    }
    master.print(1, 0, "wait done");
    Intake.Stop();
    moveRelative(-13.5, 600, 1250);
    chassis.waitUntilDone();
    stackDoinker.down();
    chassis.turnToHeading(90, 1500, {.direction=lemlib::AngularDirection::CCW_COUNTERCLOCKWISE});
    chassis.waitUntilDone();
    stackDoinker.up();
    moveRelative(-24, 600, 1250);
    chassis.waitUntilDone();
    moveRelative(3, 600, 1250);
    chassis.waitUntilDone();
    // chassis.moveToPoint(-60, -14, 1250, {.forwards=false});
    // chassis.waitUntilDone();
    // chassis.turnToHeading(90, 750);
    // chassis.waitUntilDone();
    // moveRelative(2, 600, 1500);
    // chassis.waitUntilDone();
    Intake.setSpeed(600);
    Intake.In();
    pros::delay(1500);
    Intake.Stop();
    moveRelative(32, 600, 1000);
    chassis.waitUntilDone();
    // chassis.moveToPoint(-28, -6, 1500);
    // chassis.waitUntilDone();
    float endTime = pros::millis();
    float totalTime = endTime - startTime;
    std::cout << totalTime << std::endl;
    master.print(0,0,"%f", totalTime);
}

void goalSideAWPBlue() {
    float startTime = pros::millis();
    ringColor.set_led_pwm(100);
    chassis.setPose(52,-24, 90);
    moveRelative(-20, 450, 1500);
    chassis.waitUntilDone();
    MogoMech.clamp();
    Intake.In();
    chassis.turnToPoint(24, -44, 750);
    chassis.waitUntilDone();
    chassis.moveToPoint(24, -44, 1000);
    chassis.waitUntilDone();
    while (ringColor.get_proximity() > 25) {
        pros::delay(1);
        master.print(1, 1, "waiting");
    }
    master.print(1, 1, "wait done");
    // moveRelative(-6, 600, 750);
    // chassis.waitUntilDone();
    chassis.moveToPoint(55, -32, 1250, {.forwards=false});
    chassis.waitUntilDone();
    Intake.Stop();
    MogoMech.release();
    Intake.setSpeed(250);
    chassis.moveToPose(48, 4, 0, 2500, {.horizontalDrift=18});
    Intake.In();
    chassis.waitUntilDone();
    while (!(ringColor.get_hue() > 350 || ringColor.get_hue() < 20) && ringColor.get_proximity() > 50) {
        pros::delay(1);
        master.print(1, 0, "waiting");
    }
    master.print(1, 0, "wait done");
    Intake.Stop();
    moveRelative(-10, 600, 1250);
    chassis.waitUntilDone();
    stackDoinker.down();
    chassis.turnToHeading(270, 2000, {.direction=lemlib::AngularDirection::CW_CLOCKWISE});
    chassis.waitUntilDone();
    stackDoinker.up();
    moveRelative(-24, 600, 1250);
    chassis.waitUntilDone();
    moveRelative(3, 600, 1250);
    chassis.waitUntilDone();
    // chassis.moveToPoint(-60, -14, 1250, {.forwards=false});
    // chassis.waitUntilDone();
    // chassis.turnToHeading(90, 750);
    // chassis.waitUntilDone();
    // moveRelative(2, 600, 1500);
    // chassis.waitUntilDone();
    Intake.setSpeed(600);
    Intake.In();
    pros::delay(1500);
    Intake.Stop();
    moveRelative(32, 600, 1000);
    chassis.waitUntilDone();
    // chassis.moveToPoint(-28, -6, 1500);
    // chassis.waitUntilDone();
    float endTime = pros::millis();
    float totalTime = endTime - startTime;
    std::cout << totalTime << std::endl;
    master.print(0,0,"%f", totalTime);
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

void skills() {
    float startTime = pros::millis();
    chassis.setPose(-62, 0, 90);
    Intake.In();
    pros::delay(1000);
    Intake.Out();
    chassis.moveToPoint(-46, 0, 1000);
    chassis.waitUntilDone();
    chassis.turnToHeading(0, 750);
    chassis.waitUntilDone();
    chassis.moveToPoint(-46, -20, 1500, {.forwards=false});
    chassis.waitUntilDone();
    MogoMech.clamp();
    Intake.In();
    chassis.turnToPoint(-24, -22, 750);
    chassis.waitUntilDone();
    chassis.moveToPoint(-24, -22, 1500);
    chassis.waitUntilDone();
    chassis.moveToPoint(-66, -60, 1500, {.forwards=false});
    chassis.waitUntilDone();
    float endTime = pros::millis();
    float totalTime = endTime - startTime;
    std::cout << totalTime << std::endl;
    master.print(0,0,"%f", totalTime);
}