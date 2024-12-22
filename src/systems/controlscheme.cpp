#include "api.h"
#include "pros/misc.h"
#include "systems/controlscheme.hpp"
#include "pros/rtos.hpp"
#include "systems/drive.hpp"
#include "systems/intake.hpp"
#include "systems/mogo.hpp"
#include "systems/arm.hpp"

// DT Controls
void driveControl(void* param) {
    while(true) {
        chassis.arcade(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
        pros::delay(20);
    }
}

// Intake Buttons
void intakeControl(void* param) {
    while(true) {
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            Intake.In();
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            Intake.Out();
        }
        else {
            Intake.Stop();
        };
        Intake.colorSort();
        pros::delay(20);
    }
}

// Mogo Control
void mogoControl(void* param) {
    while(true) {
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
            MogoMech.toggle();
        }
        pros::delay(20);
    }
}

void armControl(void* param) {
    while(true) {
        arm.updateState();
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
            arm.toggleReady();
        }
        else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
            arm.scoreButton();
        };

        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
            arm.raisePos();
        }
        else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
            arm.lowerPos();
        };
        pros::delay(20);
    }
}