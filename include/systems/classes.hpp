#pragma once
#include "api.h"
#include "pros/adi.hpp"

// class definitions
class Intake {

    public:
        Intake(pros::Motor floating, pros::Motor flipper); // allow for 2 seperate motors, as we have two
        void In();
        void Out();
        void setFloatingSpeed(int speed); // set the speed for the floating stage
        void setFlipperSpeed(int speed); // set the speed for the upper stage that scores the rings

    private:
        pros::Motor floating;
        pros::Motor flipper;
        int floatingSpeed;
        int flipperSpeed;
        
};

class Mogo {
    public:
        Mogo(pros::adi::Pneumatics clampPiston, pros::adi::Pneumatics tiltPiston); // set a constructor for two pistons, as that is what our system requires
        void cycleState();
        void fullPosToggle();
        void dropGoal();
        void update();
        bool clampState;
        bool tiltState;

    private:
        pros::adi::Pneumatics clampPiston;
        pros::adi::Pneumatics tiltPiston;
        int currentState; // 0 = no clamp/tilt, 1 = clamp, 2 = clamp + tilt
};