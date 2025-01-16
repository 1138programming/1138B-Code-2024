#include "api.h"
#include "classes.hpp"
#include "pros/misc.h"
#include "systems/controlscheme.hpp"
#include "pros/rtos.hpp"
#include "systems/drive.hpp"
#include "systems/intake.hpp"
#include "systems/doinker.hpp"
#include "systems/mogo.hpp"
#include "systems/arm.hpp"

// DT Controls
void driveControl() {
        chassis.opcontrol_arcade_standard(ez::SPLIT);
}

// Intake Buttons
void intakeControl(void* param) {
    while(true) {
        bool shift = master.get_digital(pros::E_CONTROLLER_DIGITAL_L1); // keep shift state updated
        if (!shift) {
            if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
                Intake.In();
            } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
                Intake.Out();
            }
            else {
                Intake.Stop();
            };
        };
        Intake.colorSort();
        pros::delay(20);
    }
}

// Doinker Buttons
void doinkerControl() {
        bool shift = master.get_digital(pros::E_CONTROLLER_DIGITAL_L1); // keep shift state updated
        if (shift) {
            if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
                rightDoinker.down();
            }
            else {
                rightDoinker.up();
            }
            if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
                leftDoinker.down();
            }
            else {
                leftDoinker.up();
            }
        }
        else {
            leftDoinker.up();
            rightDoinker.up();
        }
    }

// Mogo Control
void mogoControl() {
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
            MogoMech.toggle();
        }
        pros::delay(20);
    
}

void armControl(void* param) {
    while(true) {

        bool shift = master.get_digital(pros::E_CONTROLLER_DIGITAL_L1); // keep shift state updated

        arm.updateState(); // keep arm position updated to match state

        // right paddle
        if (shift) {
            if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
                arm.setState(Arm::ALLIANCESCORE); // score on alliance stake
            };
            if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT) && shift) {
                arm.toggleMogoTilt(); // cycle between mogo tilt and untilt positions
            };
        }
        else {
            if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y) && !shift) {
                arm.toggleReady(); // cycle between stow and load positions
            };
            if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT) && !shift) {
                arm.scoreButton(); // cycle between load and score positions
            };
            if (master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
            arm.raisePos();
            }
            else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
                arm.lowerPos();
            }
            else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
                arm.resetOffset();
            };
        };
        
        
        // left paddle
        

        //manual position offset
        pros::delay(20);
    }
}