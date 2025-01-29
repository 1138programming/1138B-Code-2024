#include "systems/classes.hpp"
#include "pros/colors.hpp"
#include "pros/optical.hpp"
#include "pros/rtos.hpp"
#include "systems/controlscheme.hpp"
#include "systems/intake.hpp"
#include <string>


//intake

Intake::Intake(pros::Motor intakeMotor_, pros::Optical ringColorSensor_)
    : intakeMotor(intakeMotor_), ringColorSensor(ringColorSensor_), state(Intake::STOP), oldColor(pros::Color::green), enableSort(true) {ringColorSensor.set_integration_time(10); ringColorSensor.set_led_pwm(100);}

void Intake::setState(States newState) {
    state = newState;
}

void Intake::Out() {
    setState(Intake::OUT);
}

void Intake::In() {
    setState(Intake::IN);
}

void Intake::Stop() {
    setState(Intake::STOP);
}

void Intake::setSortColor(pros::Color setColor_) {
    setColor = setColor_;
}

void Intake::colorSort() {
    if ((ringColorSensor.get_raw().blue > 300 && ringColorSensor.get_raw().red < 500) && ringColorSensor.get_proximity() > 200) {
        currentRingColor = pros::Color::blue;
    }
    else if ((ringColorSensor.get_raw().red > 400 && ringColorSensor.get_raw().blue < 300) && ringColorSensor.get_proximity() > 200) {
        currentRingColor = pros::Color::red;
    }
    else {
        currentRingColor = pros::Color::green;
    };
    if (enableSort && ((currentRingColor != setColor) && (currentRingColor != pros::Color::green)) && (oldColor != currentRingColor)) {
        sortNeeded = true;
        oldColor = currentRingColor;
    }
    else {
        sortNeeded = false;
    }
    oldColor = currentRingColor;
}
void Intake::setSpeed(int speed) {
    Intake::intakeSpeed = speed;
}

void Intake::updateState() {
    switch (state) {
        case STOP:
            intakeMotor.move(0);
            break;
        case IN:
            intakeMotor.move_velocity(intakeSpeed);
            if (sortNeeded) {
                sortNeeded = false;
                pros::delay(150);
                intakeMotor.move_velocity(-intakeSpeed);
                pros::delay(100);
            };
            break;
        case OUT:
            intakeMotor.move_velocity(-intakeSpeed);
    }
}

std::string Intake::getSortColor() {
    switch (setColor) {
        case pros::Color::red:
            return "Red";
            break;
        case pros::Color::blue:
            return "Blue";
            break;
        default:
            return "";
            break;
    }
}

// mogo
Mogo::Mogo(pros::adi::Pneumatics clampPiston)
    : clampPiston(clampPiston), clampState(false) {}

void Mogo::clamp() {
    clampState = true;
    clampPiston.extend();
}

void Mogo::release() {
    clampState = false;
    clampPiston.retract();
}

void Mogo::toggle() {
    clampState = !clampState;
    clampPiston.toggle();
}

bool Mogo::isClamped() {
    return clampState;
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
Arm::Arm(pros::Motor armMotor1, pros::Motor armMotor2, lemlib::PID armPID, float stowPos, float readyPos, float scorePos, float allianceScorePos, float mogoScorePos, float mogoTiltPos, float mogoUntiltPos, float gearRatio)
    : armMotor1(armMotor1), armMotor2(armMotor2), armPID(armPID), stowPos(stowPos), readyPos(readyPos), scorePos(scorePos), allianceScorePos(allianceScorePos), mogoScorePos(mogoScorePos), mogoTiltPos(mogoTiltPos), mogoUntiltPos(mogoUntiltPos),gearRatio(gearRatio), state(STOW), posOffset(0) {}

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

void Arm::resetOffset() {
    posOffset = 0;
}

void Arm::toggleReady() {
    if (state == STOW) {
        state = READY;
    }
    else {
        state = STOW;
    }
}

void Arm::toggleMogoTilt() {
    if (state == MOGOTILT) {
        state = MOGOUNTILT;
    }
    else {
        state = MOGOTILT;
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
    else {
        state = READY;
    }
}

void Arm::setState(States newState) {
    state = newState;
}

void Arm::updateState() {
    switch (state) {
        case STOW:
            setPosition = stowPos;
            break;
        case READY:
            setPosition = readyPos;
            break;
        case SCORE:
            setPosition = scorePos;
            break;
        case ALLIANCESCORE:
            setPosition = allianceScorePos;
            break;
        case MOGOTILT:
            setPosition = mogoTiltPos;
            break;
        case MOGOSCORE:
            setPosition = mogoScorePos;
            break;
        case MOGOUNTILT:
            setPosition = mogoUntiltPos;
            break;
    };
    currentPosition = (((armMotor1.get_position() * gearRatio) + (armMotor2.get_position() * gearRatio)) / 2);
    error = (setPosition + posOffset) - currentPosition;
    // master.print(0, 0, "%i ", posOffset);
    armMotor1.move(armPID.update(error));
    armMotor2.move(armPID.update(error));
}
