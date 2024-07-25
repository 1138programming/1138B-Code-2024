#include "systems/classes.hpp"


//intake

Intake::Intake(pros::Motor floating, pros::Motor flipper)
    : floating(floating), flipper(flipper) {}

void Intake::In() {
    floating.move_velocity(floatingSpeed);
    flipper.move_velocity(flipperSpeed);
}

void Intake::Out() {
    floating.move_velocity(-floatingSpeed);
    flipper.move_velocity(-flipperSpeed);
}

void Intake::Stop() {
    floating.move(0);
    flipper.move(0);
}


void Intake::setFloatingSpeed(int speed) {
    Intake::floatingSpeed = speed;
}

void Intake::setFlipperSpeed(int speed) {
    Intake::flipperSpeed = speed;
}


// mogo
Mogo::Mogo(pros::adi::Pneumatics clampPiston)
    : clampPiston(clampPiston), currentState(0) {}

void Mogo::cycleState() {
    // Increment the state or reset to 0 if it reaches 2
    if (currentState < 2) {
        currentState += 1;
    } else {
        currentState = 0;
    };
}

void Mogo::fullPosToggle() {
    if (currentState < 2) {
        currentState = 2;
    } else {
        currentState = 0;
    };
}

void Mogo::dropGoal() {
    currentState = 0;
}

void Mogo::update() {
    // Control the pistons based on the current state
    if (currentState == 0) {
        clampPiston.retract();
    } else if (currentState == 1) {
        clampPiston.extend();
    } else if (currentState == 2) {
        clampPiston.extend();
    };
}
