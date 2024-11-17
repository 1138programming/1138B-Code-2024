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
Mogo::Mogo(pros::adi::Pneumatics clampPiston) // assign constructor input
    : clampPiston(clampPiston) {}             // to class variable for piston

void Mogo::clamp() {
    // extend the piston to clamp + tilt the mogo
    clampPiston.extend();
}

void Mogo::release() {
    // retract the piston to release the mogo
    clampPiston.retract();
}

void Mogo::toggle() {
    // toggle the piston (if its clamped, release; if its released, clamp)
    clampPiston.toggle();
}

// doinker
Doinker::Doinker(pros::adi::Pneumatics doinkPiston)
    : doinkPiston(doinkPiston) {}

void Doinker::down() {
    // Increment the state or reset to 0 if it reaches 2
    doinkPiston.extend();
}

void Doinker::up() {
    doinkPiston.retract();
}

void Doinker::toggle() {
    doinkPiston.toggle();
}
