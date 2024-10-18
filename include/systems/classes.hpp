#pragma once
#include "api.h"
#include "lemlib/pid.hpp"
#include "pros/motors.h"

// class definitions
class Intake {

    public:
        Intake(pros::Motor intakeMotor);
        void In();
        void Out();
        void Stop();
        void setSpeed(int speed); // set the speed for the intake

    private:
        pros::Motor intakeMotor;
        int intakeSpeed;
        
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
        enum States {
            STOW,
            READY,
            SCOREREADY,
            SCORE
        };
        States state;
        pros::Motor armMotor1;
        pros::Motor armMotor2;
        float gearRatio;

    public:
        Arm(pros::Motor armMotor1, pros::Motor armMotor2, lemlib::PID armPID, float stowPos, float readyPos, float scoreReadyPos, float scorePos, float gearRatio);
        void toggleReady();
        void scoreButton();
        void updateState();
        void lowerPos();
        void raisePos();
        int posOffset;
        void setBrakeMode(pros::motor_brake_mode_e brakeMode);
        void setState(States newState);
        States getState();
    
};