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
    : clampPiston(clampPiston) {}

void Mogo::clamp() {
    // Increment the state or reset to 0 if it reaches 2
    clampPiston.extend();
}

void Mogo::release() {
    clampPiston.retract();
}

void Mogo::toggle() {
    clampPiston.toggle();
}
