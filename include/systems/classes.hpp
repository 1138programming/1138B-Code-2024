#pragma once
#include "api.h"
#include "lemlib/pid.hpp"
#include "pros/colors.hpp"
#include "pros/motors.h"
#include "pros/optical.hpp"

// class definitions
class Intake {

    public:
        Intake(pros::Motor intakeMotor, pros::Optical ringColorSensor);
        void In();
        void Out();
        void Stop();
        void setSpeed(int speed); // set the speed for the intake
        void setSortColor(pros::Color setColor);
        void colorSort();
        pros::Color currentRingColor;

    private:
        pros::Optical ringColorSensor;
        pros::Motor intakeMotor;
        pros::Color setColor;
        int intakeSpeed;
        bool sortNeeded;
        
};

class Mogo {
    public:
        Mogo(pros::adi::Pneumatics clampPiston); // set a constructor for two pistons, as that is what our system requires
        void clamp();
        void release();
        void toggle();

    private:
        pros::adi::Pneumatics clampPiston;
};

class Doinker {
    public:
        Doinker(pros::adi::Pneumatics doinkPiston); // set a constructor for two pistons, as that is what our system requires
        void down();
        void up();
        void toggle();

    private:
        pros::adi::Pneumatics doinkPiston;
};

class Arm {
    private:
        float setPosition;
        float currentPosition;
        float error;
        lemlib::PID armPID;
        float stowPos;
        float readyPos;
        float scoreReadyPos;
        float scorePos;
        pros::Motor armMotor1;
        pros::Motor armMotor2;
        float gearRatio;

    public:
        Arm(pros::Motor armMotor1, pros::Motor armMotor2, lemlib::PID armPID, float stowPos, float readyPos, float scoreReadyPos, float scorePos, float gearRatio);
        enum States {
            STOW,
            READY,
            SCOREREADY,
            SCORE
        };
        States state;
        States getState();
        void toggleReady();
        void scoreButton();
        void updateState();
        void lowerPos();
        void raisePos();
        int posOffset;
        void setBrakeMode(pros::motor_brake_mode_e brakeMode);
        void setState(States newState);
    
};