#pragma once
#include "api.h"

// class definitions
class Intake {

    public:
        Intake(pros::Motor floating, pros::Motor flipper); // allow for 2 seperate motors, as we have two
        void In(); // spin the intake forwards (intake)
        void Out(); // spin the intake in reverse (outtake)
        void Stop(); // stop the intake
        void setFloatingSpeed(int speed); // set the speed for the floating stage
        void setFlipperSpeed(int speed); // set the speed for the hook chain

    private:
        pros::Motor floating; // stores the floating stage motor
        pros::Motor flipper; // stores the hook chain motor
        int floatingSpeed; // floating stage speed
        int flipperSpeed; // hook speed
        
};

class Mogo {

    public:
        Mogo(pros::adi::Pneumatics clampPiston, pros::adi::Pneumatics tiltPiston); // create a constructor for two pistons
        void cycleState(); // cycle between release, clamp, and clamp + tilt states 
        void fullPosToggle(); // toggle between release and clamp + tilt
        void dropGoal(); // instantly switch to the release state
        void update(); // sets the pneumatics based on the current state value
        bool clampState; // variable storing the clamp state (true if clamped)
        bool tiltState; // variable storing the tilt state (true if tilted)

    private:
        pros::adi::Pneumatics clampPiston; // variable storing the clamp piston
        pros::adi::Pneumatics tiltPiston; // variable storing the tilt piston
        int currentState; // variable storing the current state (0 = release, 1 = clamp, 2 = clamp + tilt)
};