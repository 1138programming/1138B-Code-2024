#pragma once
#include "api.h"

// class definitions
class Intake {

    public:
        Intake(pros::Motor floating, pros::Motor flipper); // allow for 2 seperate motors, as we have two
        void In();
        void Out();
        void Stop();
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
        Mogo(pros::adi::Pneumatics clampPiston); // set a constructor for two pistons, as that is what our system requires
        void clamp();
        void release();
        void toggle();

    private:
        pros::adi::Pneumatics clampPiston;
};