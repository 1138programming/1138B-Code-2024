#include "api.h"
#include "systems/controlscheme.hpp"
#include "pros/misc.h"
#include "systems/drive.hpp"
#include "systems/intake.hpp"
#include "systems/mogo.hpp"

// DT Controls
void driveControl() {
    chassis.tank(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));
}

// Intake Buttons
void intakeControl() {
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        Intake.In();
    } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        Intake.Out();
    };
}

// Mogo Control
void mogoControl() {
    MogoMech.update();
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        MogoMech.dropGoal();
    } else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2) && !master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        MogoMech.cycleState();
    } else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2) && master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        MogoMech.fullPosToggle();
    }
}