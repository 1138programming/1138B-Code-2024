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
        Mogo(pros::adi::Pneumatics clampPiston); // set a constructor for one piston
        void clamp(); // clamp and tilt the mogo
        void release(); // release the mogo
        void toggle(); // toggle between clamp + tilt and release

    private:
        pros::adi::Pneumatics clampPiston; // variable for our clamp piston
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