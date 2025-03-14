#include "api.h"
#include "lemlib/chassis/chassis.hpp"
#include "pros/rtos.hpp"
#include "systems/classes.hpp"
#include "systems/drive.hpp"
#include "systems/mogo.hpp"
#include "systems/intake.hpp"
#include "autos.hpp"
#include "systems/controlscheme.hpp"
#include "systems/arm.hpp"
#include "systems/doinker.hpp"
#include "systems/distanceReset.hpp"
#include "systems/distanceSensors.hpp"



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

void soloAWPFullRed() {
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

void soloAWPFullBlue() {
    chassis.setPose(60, 18, 180);
    arm.setState(Arm::READY);
    Intake.In();
    chassis.moveToPoint(60, 12, 750);
    chassis.waitUntilDone();
    chassis.turnToHeading(135, 750);
    chassis.waitUntilDone();
    Intake.Stop();
    arm.setState(Arm::ALLIANCESCORE);
    pros::delay(500);
    chassis.moveToPose(28, 24, 90, 1500, {.forwards=false, .horizontalDrift=16});
    chassis.waitUntil(6);
    arm.setState(Arm::STOW);
    chassis.waitUntilDone();
    MogoMech.clamp();
    chassis.turnToPoint(24, 44, 750);
    Intake.In();
    chassis.waitUntilDone();
    chassis.moveToPoint(24, 44, 1000);
    chassis.waitUntilDone();
    chassis.moveToPose(49, 7, 180, 2500);
    chassis.waitUntil(12);
    intakeLift.extend();
    chassis.waitUntilDone();
    intakeLift.retract();
    moveRelative(-6, 127, 750);
    chassis.waitUntilDone();
    chassis.moveToPoint(48, -24, 1500);
    chassis.waitUntil(8);
    Intake.Stop();
    MogoMech.release();
    chassis.waitUntilDone();
    chassis.turnToHeading(90, 750);
    chassis.waitUntilDone();
    chassis.moveToPoint(31, -24, 1500, {.forwards=false, .earlyExitRange=3});
    Intake.Out();
    chassis.waitUntilDone();
    chassis.moveToPoint(27, -24, 1000, {.maxSpeed=75});
    chassis.waitUntilDone();
    MogoMech.clamp();
    Intake.In();
    chassis.turnToPoint(24, -44, 750);
    chassis.waitUntilDone();
    Intake.In();
    chassis.moveToPoint(24, -44, 1000);
    chassis.waitUntilDone();
    arm.setState(Arm::SCORE);
    chassis.moveToPoint(10, -12, 1250, {.forwards=false});
    chassis.waitUntil(8);
    Intake.Stop();
    chassis.waitUntilDone();
    arm.setState(Arm::READY);
}

void ringSideMiddleRed() {
    chassis.setPose(-60, 18, 180);
    arm.setState(Arm::READY);
    Intake.In();
    chassis.moveToPoint(-60, 12, 500);
    chassis.waitUntilDone();
    chassis.turnToHeading(225, 500);
    chassis.waitUntilDone();
    Intake.Stop();
    arm.setState(Arm::ALLIANCESCORE);
    pros::delay(500);
    chassis.moveToPose(-28, 24, 270, 1500, {.forwards=false, .horizontalDrift=16});
    chassis.waitUntil(6);
    arm.setState(Arm::STOW);
    chassis.waitUntilDone();
    MogoMech.clamp();
    chassis.turnToPoint(-7, 48, 500);
    chassis.waitUntilDone();
    Intake.In();
    chassis.moveToPose(-7, 48, 0, 1500, {.earlyExitRange=16});
    chassis.waitUntilDone();
    chassis.moveToPoint(-8.5, 55, 1000);
    chassis.waitUntilDone();
    chassis.moveToPoint(-24, 48, 1000);
    chassis.waitUntilDone();
    chassis.turnToPoint(-64, 64, 600);
    chassis.waitUntilDone();
    chassis.moveToPose(-63, 63, 315, 1300, {.horizontalDrift=100, .earlyExitRange=12});
    chassis.waitUntilDone();
    chassis.tank(127, 127);
    while (ringColor.get_proximity() < 200) {};
    chassis.tank(0, 0);
    moveRelative(-5, 127, 500);
    chassis.waitUntilDone();
    intakeLift.extend();
    chassis.tank(127, 127);
    pros::delay(500);
    chassis.tank(0, 0);
    intakeLift.retract();
    moveRelative(-6, 127, 500);
    chassis.waitUntilDone();
    chassis.turnToPoint(-48, 0, 500);
    chassis.waitUntilDone();
    chassis.moveToPose(-48, 7, 180, 1500);
    intakeLift.extend();
    chassis.waitUntilDone();
    moveRelative(-6, 127, 500);
    chassis.waitUntilDone();
    intakeLift.retract();
    chassis.moveToPoint(-30, 8, 1000);
    chassis.waitUntilDone();
    arm.setState(Arm::SCORE);

}

void ringSideMiddleBlue() {
    chassis.setPose(60, 18, 180);
    arm.setState(Arm::READY);
    Intake.In();
    chassis.moveToPoint(60, 12, 500);
    chassis.waitUntilDone();
    chassis.turnToHeading(135, 500);
    chassis.waitUntilDone();
    Intake.Stop();
    arm.setState(Arm::ALLIANCESCORE);
    pros::delay(500);
    chassis.moveToPose(28, 24, 90, 1500, {.forwards=false, .horizontalDrift=16});
    chassis.waitUntil(6);
    arm.setState(Arm::STOW);
    chassis.waitUntilDone();
    MogoMech.clamp();
    chassis.turnToPoint(7, 48, 500);
    chassis.waitUntilDone();
    Intake.In();
    chassis.moveToPose(7, 48, 0, 1500, {.earlyExitRange=16});
    chassis.waitUntilDone();
    chassis.moveToPoint(8.5, 55, 1000);
    chassis.waitUntilDone();
    chassis.moveToPoint(24, 48, 1000);
    chassis.waitUntilDone();
    chassis.turnToPoint(64, 64, 600);
    chassis.waitUntilDone();
    chassis.moveToPose(63, 63, 45, 1300, {.horizontalDrift=100, .earlyExitRange=12});
    chassis.waitUntilDone();
    chassis.tank(127, 127);
    while (ringColor.get_proximity() < 200) {};
    chassis.tank(0, 0);
    moveRelative(-5, 127, 500);
    chassis.waitUntilDone();
    intakeLift.extend();
    chassis.tank(127, 127);
    pros::delay(500);
    chassis.tank(0, 0);
    intakeLift.retract();
    moveRelative(-6, 127, 500);
    chassis.waitUntilDone();
    chassis.turnToPoint(48, 0, 500);
    chassis.waitUntilDone();
    chassis.moveToPose(50, 7, 180, 1500);
    intakeLift.extend();
    chassis.waitUntilDone();
    moveRelative(-6, 127, 500);
    chassis.waitUntilDone();
    chassis.moveToPoint(30, 8, 1000);
    chassis.waitUntil(3);
    intakeLift.retract();
    chassis.waitUntilDone();
    arm.setState(Arm::SCORE);

}

void stateSkills(){

 ///////////////////////////////////////////////
  //--------------FIRST SECTION----------------//
  ///////////////////////////////////////////////

  chassis.setPose(-63.5, 0, 90);

  //-----------ALLIANCE STAKE------------------//

  Intake.In();
  pros::delay(500);
  Intake.Stop();

  //-----------CLAMP FIRST MOGO------------------//

  chassis.moveToPoint(-48, 0, 850, {.forwards = true, .maxSpeed = 100});
  chassis.waitUntilDone();

  chassis.turnToPoint(-48, -24, 450);
  chassis.waitUntilDone();

  chassis.moveToPoint(-48, 24, 1000, {.forwards=false, .maxSpeed = 70});
  chassis.waitUntilDone();

  MogoMech.clamp();

//-----------SCORE ONE RING------------------//

  chassis.turnToPoint(-32, 24, 450);
  chassis.waitUntilDone();

  Intake.In();

  chassis.moveToPoint(-32, 24, 750, {.forwards=true, .maxSpeed = 100});
  chassis.waitUntilDone();


  //-----------OBTAIN 2nd RING------------------//

  //chassis.turnToPoint(24, 48, 500);
  //chassis.waitUntilDone();

  chassis.moveToPoint(24, 48, 1750, {.forwards=true, .maxSpeed = 100});
  pros::delay(1000);
  arm.setState(Arm::READY);
  chassis.waitUntilDone();

  chassis.moveToPoint(0, 44, 1000, {.forwards=false, .maxSpeed = 100});
  chassis.waitUntilDone();
  arm.setState(Arm::READY2);
  Intake.Stop();
  pros::delay(100);
  Intake.In();

  //-----------LADY BROWN 1------------------//

  chassis.turnToPoint(3, 65, 500);
  chassis.waitUntilDone();
 
  chassis.moveToPose(3, 68, 0, 1000, {.forwards=true, .horizontalDrift=30, .maxSpeed =90});
  chassis.waitUntilDone();

  chassis.setPose(0, 61, chassis.getPose().theta);

  arm.setState(Arm::SCORE);
  pros::delay(450);

  //-----------SCORE THREE RINGS------------------//

  chassis.moveToPoint(0, 48, 750, {.forwards=false, .maxSpeed = 100});
  chassis.waitUntilDone();
  arm.setState(Arm::STOW);


  chassis.turnToPoint(-33, 48, 500);
  chassis.waitUntilDone();

  chassis.moveToPoint(-33, 48, 1000, {.forwards=true, .maxSpeed = 90});
  chassis.waitUntilDone();

  chassis.moveToPoint(-60, 48, 1750, {.forwards=true, .maxSpeed = 60});
  chassis.waitUntilDone();

 // chassis.turnToPoint(-49, 57, 500);
  //chassis.waitUntilDone();

  chassis.moveToPoint(-42, 62, 1000, {.forwards=true});
  chassis.waitUntilDone();

  //-----------Place in corner------------------//

  //chassis.turnToPoint(-59, 59, 500, {.forwards = false});
 // chassis.waitUntilDone();

  chassis.moveToPoint(-62, 62, 1000, {.forwards=false});
  chassis.waitUntilDone();

  MogoMech.release();
  Intake.Stop();

  pros::delay(250);
//   chassis.moveToPoint(-48, 48, 750, {.forwards=true, .maxSpeed =100});
//   chassis.waitUntilDone();
  
  //RESET//
//   chassis.turnToHeading(90, 750);
//   chassis.waitUntilDone();

//   resetRobotPos(leftDistance, "positive_y");
//   resetRobotPos(backDistance, "negative_x");
    
  Intake.In();
  arm.setState(Arm::READY);

  ///////////////////////////////////////////////
  //--------------2ND SECTION----------------//
  ///////////////////////////////////////////////

  //Get ring for alliance stake

  chassis.moveToPoint(35, 50, 2500, {.forwards=true});
  chassis.waitUntilDone();

 
// //   chassis.turnToHeading(90,750);
// //   chassis.waitUntilDone();

// //   resetRobotPos(leftDistance, "positive_y");
// //   resetRobotPos(frontDistance, "positive_x");

//   //Clamp second goal
  rightDoinker.down();
  chassis.turnToPoint(54, 26 , 750, {.forwards = false});
//   Intake.In();

//   chassis.waitUntilDone();
//   rightDoinker.up();


  chassis.moveToPoint(54, 26, 1000, {.forwards=false});
  chassis.waitUntilDone();
  MogoMech.clamp();
  //put in corner
  chassis.turnToPoint(64, 54, 500);
  arm.setState(Arm::READY2);
  pros::delay(150);
  Intake.Out();
  chassis.waitUntilDone();


  chassis.moveToPoint(64, 54, 1000, {.forwards=true});
  chassis.waitUntilDone();

  chassis.turnToHeading(270, 850);
  pros::delay(500);
  rightDoinker.up();
  chassis.waitUntilDone();
  pros::delay(150);

  chassis.turnToPoint(64, 64, 500, {.forwards=false, .maxSpeed = 70});
  chassis.waitUntilDone();

  chassis.moveToPoint(64, 64, 500, {.forwards=false, .maxSpeed =50});
  chassis.waitUntilDone();
    MogoMech.release();


//   Intake.In();



//   //get third goal
//   Intake.In();

//   chassis.moveToPoint(48, 30, 1150, {.forwards=true, .maxSpeed =100});
//   chassis.waitUntilDone();

//   chassis.turnToHeading(0, 750);
//   chassis.waitUntilDone();
//   resetRobotPos(rightDistance, "positive_x");
//   resetRobotPos(frontDistance, "positive_y");
 

//   chassis.moveToPoint(48, 0, 1150, {.forwards=false, .maxSpeed =70});
//   Intake.Stop();
//   chassis.waitUntilDone();
//   resetRobotPos(rightDistance, "positive_x");
//   resetRobotPos(frontDistance, "positive_y");
//   MogoMech.clamp();


//   //score alliance stake

//   chassis.turnToPoint(63, 0, 750, {.forwards=true});
//   chassis.waitUntilDone();
//   resetRobotPos(leftDistance, "positive_y");
//   resetRobotPos(frontDistance, "positive_x");

//   chassis.moveToPoint(63, 0, 1000, {.forwards=true, .maxSpeed =60});
//   chassis.waitUntilDone();
//   chassis.setPose(61, 0, chassis.getPose().theta);

//   chassis.moveToPoint(57, 0, 500, {.forwards=false, .maxSpeed =80});
//   chassis.waitUntilDone();
//   arm.setState(Arm::MOGOSCORE);

//   chassis.moveToPoint(54, 0, 500, {.forwards=false, .maxSpeed =60});
//   chassis.waitUntilDone();

//   arm.setState(Arm::ALLIANCESCORE);
//   pros::delay(250); 

//   chassis.moveToPoint(48, 0, 500, {.forwards=false, .maxSpeed =80});
//   pros::delay(250);
//   Intake.In();
//   arm.setState(Arm::STOW);
//   chassis.waitUntilDone();

//   chassis.turnToHeading(0, 500);
//   chassis.waitUntilDone();
//   resetRobotPos(frontDistance, "positive_y");
//   resetRobotPos(rightDistance, "positive_x");

//   chassis.moveToPoint(48, 24, 900, {.forwards=true, .maxSpeed =90});
//   chassis.waitUntilDone();

//   chassis.turnToHeading(270, 750);
//   chassis.waitUntilDone();
//   resetRobotPos(rightDistance, "positive_y");
//   resetRobotPos(backDistance, "positive_x");

//   ///////////////////////////////////////////////
//   //--------------3RD SECTION----------------//
//   ///////////////////////////////////////////////

//   //score one ring


//   chassis.moveToPoint(24, 24, 850, {.forwards=true, .maxSpeed =90});
//   chassis.waitUntilDone();

//   chassis.turnToHeading(270, 750);
//   chassis.waitUntilDone();
//   resetRobotPos(rightDistance, "positive_y");
//   resetRobotPos(backDistance, "positive_x");


// //cross under ladder score 3
//   chassis.turnToPoint(-15, -15, 500);
//   chassis.waitUntilDone();
//   Intake.Stop();

//   chassis.moveToPoint(-15, -15, 1350, {.forwards=true, .maxSpeed =90});
//   chassis.waitUntilDone();
//   Intake.In();


//   chassis.moveToPoint(-48, -48, 1650, {.forwards=true, .maxSpeed =70});
//   chassis.waitUntilDone();

//   //score two and corner
//   //chassis.turnToPoint(-62, -48, 500);
//   chassis.turnToHeading(270, 750);
//   chassis.waitUntilDone();
//   resetRobotPos(leftDistance, "negative_y");
//   resetRobotPos(frontDistance, "negative_x");


//   chassis.moveToPoint(-63, -48, 850, {.forwards=true, .maxSpeed =80});
//   chassis.waitUntilDone();


//   //chassis.turnToPoint(-45, -62, 500);
//   //chassis.waitUntilDone();

//   chassis.moveToPoint(-50, -60, 1000, {.forwards=true, .maxSpeed =100});
//   chassis.waitUntilDone();

//   //-----------Place in corner------------------//

//  // chassis.turnToPoint(-56, -62, 500, {.forwards 1d`s= false});
//  // chassis.waitUntilDone();

//   chassis.moveToPoint(-60, -62, 750, {.forwards=false, .maxSpeed =100});
//   chassis.waitUntilDone();


// //   linearController.kD = 3;
// //   angularController.kD = 19;
  
//   //chassis.turnToPoint(-48, -48, 500);
//   //chassis.waitUntilDone();
//   MogoMech.release();
//   Intake.Stop();



//   chassis.moveToPoint(-48, -48, 750, {.forwards=true, .maxSpeed =100});
//   chassis.waitUntilDone();
  
//   //RESET//
//   chassis.turnToHeading(180, 750);
//   chassis.waitUntilDone();

// ///////////////////////////////////////////////
//   //--------------4th SECTION----------------//
//   ///////////////////////////////////////////////

//   //clamp and one ring
//   resetRobotPos(frontDistance, "negative_y");
//   resetRobotPos(rightDistance, "negative_x");
  
//   chassis.turnToPoint(-48, -24, 500, {.forwards = false});
//   chassis.waitUntilDone();

//   chassis.moveToPoint(-48, -24, 1150, {.forwards=false, .maxSpeed =70});
//   chassis.waitUntilDone();
//   MogoMech.clamp();
//   arm.setState(Arm::READY);

//   chassis.turnToPoint(-24, -48, 500);
//   chassis.waitUntilDone();
//   Intake.In();

//   chassis.moveToPoint(-24, -48, 1000, {.forwards=true, .maxSpeed =100});
//   chassis.waitUntilDone();

// //lady brown stuff

//   chassis.turnToPoint(0, -45, 500, {.forwards = true});
//   chassis.waitUntilDone();

//   chassis.moveToPoint(0, -45, 850, {.forwards=true, .maxSpeed = 100});
//   chassis.waitUntilDone();
//   arm.setState(Arm::READY2);
//   Intake.Stop();
//   pros::delay(100);
//   Intake.In();

//   //-----------LADY BROWN 1------------------//

//   chassis.turnToPoint(0, -63, 500);
//   chassis.waitUntilDone();
 
//   chassis.moveToPoint(0, -63, 850, {.forwards=true, .maxSpeed =80});
//   chassis.waitUntilDone();

//   chassis.setPose(0,-61, chassis.getPose().theta);
//   pros::delay(50);
//   arm.setState(Arm::SCORE);
//   pros::delay(350);

//   chassis.moveToPoint(0, -48, 750, {.forwards=false, .maxSpeed = 100});
//   chassis.waitUntilDone();
//   arm.setState(Arm::STOW);

//   //now score rings

//   Intake.In();

//   chassis.turnToPoint(24, -48, 750);
//   chassis.waitUntilDone();

//   chassis.moveToPoint(24, -48, 1000, {.forwards=true, .maxSpeed =100});
//   chassis.waitUntilDone();
//   resetRobotPos(rightDistance, "negative_y");
//   resetRobotPos(frontDistance, "positive_x");


//   chassis.turnToHeading(0, 750);
//   chassis.waitUntilDone();
//   resetRobotPos(backDistance, "negative_y");
//   resetRobotPos(rightDistance, "positive_x");


//   chassis.moveToPoint(24, -24, 1150, {.forwards=true, .maxSpeed =100});
//   chassis.waitUntilDone();

//         Intake.enableSort = false;



//   chassis.turnToPoint(44, -44, 500);
//   chassis.waitUntilDone();

//   chassis.moveToPoint(44, -44, 850, {.forwards=true, .maxSpeed =100});
//   Intake.In();
//   chassis.waitUntilDone();



//   //score two and corner
//   //chassis.turnToPoint(60, -48, 500);
//   //chassis.waitUntilDone();

//   chassis.moveToPoint(60, -48, 750, {.forwards=true, .maxSpeed =70});
//   chassis.waitUntilDone();

//  chassis.moveToPoint(24, -48, 850, {.forwards=false, .maxSpeed =100});
//  chassis.waitUntilDone();

//  // chassis.turnToPoint(48, -56, 500);
//   //chassis.waitUntilDone();
//   ////rightDoinker.down();

//   chassis.moveToPoint(48, -60, 500, {.forwards=true, .maxSpeed =100});
//   //rightDoinker.down();
//   chassis.waitUntilDone();

//   //rightDoinker.down();

//   chassis.moveToPoint(55, -63, 650, {.forwards=true, .maxSpeed =100});
//   chassis.waitUntilDone();



// chassis.turnToPoint(62, -63, 1450, {.forwards = false,.direction = lemlib::AngularDirection::CCW_COUNTERCLOCKWISE, .maxSpeed = 65});
// pros::delay(1250);
//   Intake.Stop();

// chassis.waitUntilDone();
//     //rightDoinker.up();


//   chassis.moveToPoint(64, -63, 500, {.forwards=false, .maxSpeed =127});
//   chassis.waitUntilDone();
//     MogoMech.release();

//   //HANGGG
//   chassis.moveToPoint(24, -24, 500, {.forwards=true, .maxSpeed =127});
//   chassis.waitUntilDone();

//   chassis.turnToPoint(64, -64, 500);
//   chassis.waitUntilDone();
//   arm.setState(Arm::SCORE);

//   chassis.moveToPoint(0, -0, 2000, {.forwards=false, .maxSpeed =127});
//   chassis.waitUntilDone();
}

void pidTester() {
    chassis.setPose(0,0,0);
    chassis.moveToPoint(0, 24, 10000);
}