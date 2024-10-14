#include "systems/classes.hpp"


//intake

Intake::Intake(pros::Motor intakeMotor_)
    : intakeMotor(intakeMotor_) {}

void Intake::In() {
    intakeMotor.move_velocity(intakeSpeed);
}

void Intake::Out() {
    intakeMotor.move_velocity(-intakeSpeed);
}

void Intake::Stop() {
    intakeMotor.move(0);
}


void Intake::setSpeed(int speed) {
    Intake::intakeSpeed = speed;
}


// mogo
Mogo::Mogo(pros::adi::Pneumatics clampPiston)
    : clampPiston(clampPiston) {}

void Mogo::clamp() {
    clampPiston.extend();
}

void Mogo::release() {
    clampPiston.retract();
}

void Mogo::toggle() {
    clampPiston.toggle();
}

// doinker
Doinker::Doinker(pros::adi::Pneumatics doinkPiston)
    : doinkPiston(doinkPiston) {}

void Doinker::down() {
    doinkPiston.extend();
}

void Doinker::up() {
    doinkPiston.retract();
}

void Doinker::toggle() {
    doinkPiston.toggle();
}


//arm
Arm::Arm(pros::Motor armMotor, lemlib::PID armPID, float stowPos, float readyPos, float scoreReadyPos, float scorePos, float gearRatio)
    : armMotor(armMotor), armPID(armPID), stowPos(stowPos), readyPos(readyPos), scoreReadyPos(scoreReadyPos), scorePos(scorePos), gearRatio(gearRatio), state(STOW) {}

void Arm::toggleReady() {
    if (state == STOW) {
        state = READY;
    }
    else {
        state = STOW;
    }
}

void Arm::scoreButton() {
    if (state == READY) {
        state = SCOREREADY;
    }
    else if (state == SCOREREADY) {
        state = SCORE;
    }
    else {
        state = READY;
    }
}

void Arm::updateState() {
    switch (state) {
        case STOW:
            setPosition = stowPos;
            break;
        case READY:
            setPosition = readyPos;
            break;
        case SCOREREADY:
            setPosition = scoreReadyPos;
            break;
        case SCORE:
            setPosition = scorePos;
            break;
    };
    currentPosition = (armMotor.get_position() * gearRatio);
    error = setPosition - currentPosition;
    armMotor.move(armPID.update(error));
}