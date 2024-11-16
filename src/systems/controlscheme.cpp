#include "api.h"
#include "pros/misc.h"
#include "systems/controlscheme.hpp"
#include "systems/drive.hpp"
#include "systems/intake.hpp"
#include "systems/mogo.hpp"
#include "systems/doinker.hpp"
#include "systems/arm.hpp"

// DT Controls
void driveControl() {
    chassis.arcade(master.get_analog(ANALOG_LEFT_Y), master.get_analog(ANALOG_RIGHT_X));
}

// Intake Buttons
void intakeControl() {
    if (master.get_digital(DIGITAL_R2)) {
        Intake.In();
    } else if (master.get_digital(DIGITAL_R1)) {
        Intake.Out();
    }
    else {
        Intake.Stop();
    };
    Intake.colorSort(NULL);
}

// Mogo Control
void mogoControl() {
    if (master.get_digital_new_press(DIGITAL_L2)) {
        MogoMech.toggle();
    }
    Intake.colorSort(NULL);
}

// Doinker Control
void doinkerControl() {
    if (master.get_digital(DIGITAL_L1)) {
        stackDoinker.down();
    }
    else {
        stackDoinker.up();
    };
}

void armControl() {
    arm.updateState();
    if (master.get_digital_new_press(DIGITAL_Y)) {
        arm.toggleReady();
    }
    else if (master.get_digital_new_press(DIGITAL_RIGHT)) {
        arm.scoreButton();
    };

    if (master.get_digital(DIGITAL_UP)) {
        arm.raisePos();
    }
    else if (master.get_digital(DIGITAL_DOWN)) {
        arm.lowerPos();
    };
}