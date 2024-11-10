#include "systems/classes.hpp"
#include "pros/colors.hpp"
#include "pros/optical.hpp"
#include "pros/rtos.hpp"
#include "systems/controlscheme.hpp"
#include "systems/intake.hpp"


//intake

Intake::Intake(pros::Motor intakeMotor_, pros::Optical ringColorSensor_)
    : intakeMotor(intakeMotor_), ringColorSensor(ringColorSensor_) {}

void Intake::Out() {
    intakeMotor.move_velocity(-intakeSpeed);
}

void Intake::In() {
    intakeMotor.move_velocity(intakeSpeed);
    // if (sortNeeded) {
    //     sortNeeded = false;
    //     pros::delay(60);
    //     Intake::Out();
    //     pros::delay(100);
    // }
}

void Intake::Stop() {
    intakeMotor.move(0);
}

void Intake::setSortColor(pros::Color setColor_) {
    setColor = setColor_;
}

void Intake::colorSort() {
    // pros::Color oldColor = pros::Color::green;
    // if ((ringColorSensor.get_hue() > 200 && ringColorSensor.get_hue() < 230) && ringColorSensor.get_proximity() > 25) {
    //     currentRingColor = pros::Color::blue;
    // }
    // else if ((ringColorSensor.get_hue() > 350 || ringColorSensor.get_hue() < 20) && ringColorSensor.get_proximity() > 50) {
    //     currentRingColor = pros::Color::red;
    // }
    // else {
    //     currentRingColor = pros::Color::green;
    // };
    // if (currentRingColor != setColor && oldColor != currentRingColor) {
    //     sortNeeded = true;
    //     oldColor = currentRingColor;
    // }
    // else {
    //     sortNeeded = false;
    // }
    // oldColor = currentRingColor;
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
Arm::Arm(pros::Motor armMotor1, pros::Motor armMotor2, lemlib::PID armPID, float stowPos, float readyPos, float scoreReadyPos, float scorePos, float gearRatio)
    : armMotor1(armMotor1), armMotor2(armMotor2), armPID(armPID), stowPos(stowPos), readyPos(readyPos), scoreReadyPos(scoreReadyPos), scorePos(scorePos), gearRatio(gearRatio), state(STOW), posOffset(0) {}

void Arm::setBrakeMode(pros::motor_brake_mode_e brakeMode) {
    armMotor1.set_brake_mode(brakeMode);
    armMotor2.set_brake_mode(brakeMode);
}

void Arm::lowerPos() {
    posOffset--;
}

void Arm::raisePos() {
    posOffset++;
}

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
        // Intake.In();
        // pros::delay(100);
        // Intake.Stop();
        // pros::delay(50);
        // Intake.In();
        // pros::delay(100);
        // Intake.Stop();
        state = SCORE;
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
    currentPosition = (armMotor1.get_position() * gearRatio);
    error = (setPosition + posOffset) - currentPosition;
    master.print(0, 0, "%i ", posOffset);
    armMotor1.move(armPID.update(error));
    armMotor2.move(armPID.update(error));
}
