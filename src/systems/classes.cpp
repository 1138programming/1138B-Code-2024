#include "systems/classes.hpp"


//intake

Intake::Intake(pros::Motor floating, pros::Motor flipper) // assigns constructor values for
    : floating(floating) , flipper(flipper) {}            // motors to the associated class values

void Intake::In() {
    floating.move_velocity(floatingSpeed); // set the floating stage to the set speed (forward direction)
    flipper.move_velocity(flipperSpeed); // set the hook stage to the set speed (forward direction)
}

void Intake::Out() {
    floating.move_velocity(-floatingSpeed); // set the floating stage to the set speed (reverse direction)
    flipper.move_velocity(-flipperSpeed); // set the hook stage to the set speed (reverse direction)
}

void Intake::Stop() {
    floating.move(0); // stop the floating stage motor
    flipper.move(0); // stop the hook stage motor
}

void Intake::setFloatingSpeed(int speed) {
    Intake::floatingSpeed = speed; // set the class variable for floating stage speed to the function input
}

void Intake::setFlipperSpeed(int speed) {
    Intake::flipperSpeed = speed; // set the class variable for hook stage speed to the function input
}


// mogo
Mogo::Mogo(pros::adi::Pneumatics clampPiston, pros::adi::Pneumatics tiltPiston) // assigns constructor inputs to class
    : clampPiston(clampPiston), tiltPiston(tiltPiston), currentState(0) {}      // and sets default state to released

void Mogo::cycleState() {
    // Increment the state or reset to 0 (released) if it reaches 2 (clamp + tilt)
    if (currentState < 2) {
        currentState += 1;
    } else {
        currentState = 0;
    };
}

void Mogo::fullPosToggle() {
    // Toggle between 0 (released) and 2 (clamp + tilt)
    if (currentState < 2) {
        currentState = 2;
    } else {
        currentState = 0;
    };
}

void Mogo::dropGoal() {
    // Set state to 0 (released)
    currentState = 0;
}

void Mogo::update() {
    // Control the pistons based on the current state
    if (currentState == 0) {
        clampPiston.retract();
        tiltPiston.retract();
    } else if (currentState == 1) {
        clampPiston.extend();
        tiltPiston.retract();
    } else if (currentState == 2) {
        clampPiston.extend();
        tiltPiston.extend();
    };
}
