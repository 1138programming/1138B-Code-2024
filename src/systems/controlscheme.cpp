#include "api.h"
#include "systems/controlscheme.hpp"
#include "systems/drive.hpp"
#include "systems/intake.hpp"
#include "systems/mogo.hpp"

// DT Controls
void driveControl() {
    chassis.tank(master.get_analog(ANALOG_LEFT_Y), master.get_analog(ANALOG_RIGHT_Y));
}

// Intake Buttons
void intakeControl() {
    if (master.get_digital(DIGITAL_R2)) {
        Intake.In();
    } else if (master.get_digital(DIGITAL_R1)) {
        Intake.Out();
    };
}

// Mogo Control
void mogoControl() {
    MogoMech.update();
    if (master.get_digital(DIGITAL_L1)) {
        MogoMech.dropGoal();
    } else if (master.get_digital_new_press(DIGITAL_L2) && !master.get_digital(DIGITAL_DOWN)) {
        MogoMech.cycleState();
    } else if (master.get_digital_new_press(DIGITAL_L2) && master.get_digital(DIGITAL_DOWN)) {
        MogoMech.fullPosToggle();
    }
}