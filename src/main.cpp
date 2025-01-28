#include "main.h"
#include "liblvgl/llemu.hpp"
#include "pros/colors.hpp"
#include "pros/motors.h"
#include "systems/classes.hpp"
#include "systems/drive.hpp"
#include "systems/intake.hpp"
#include "systems/arm.hpp"
#include "systems/controlscheme.hpp"
#include "autos.hpp"
#include "taskmanager/taskmanager.hpp"
#include "screen/screen.hpp"
#include <cstddef>


TaskWrapper intakeControlThread(intakeControl, nullptr, "Intake Control");
TaskWrapper armControlThread(armControl, nullptr, "Arm Control");

TaskManager controlsManager;



/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void initilizeControls() {
	controlsManager.addTask(&intakeControlThread);
	controlsManager.addTask(&armControlThread);
	controlsManager.startAllTasks();
}

void initialize() {

	pros::delay(500);

	newScreen.init(10);
	chassis.calibrate();

	Intake.setSpeed(600);
	arm.setBrakeMode(MOTOR_BRAKE_HOLD);
	Intake.setSortColor(pros::Color::blue);

	initilizeControls();

	armMotor1.tare_position();
	armMotor2.tare_position();

	
	pros::Task([&] {
        while (true) {
            auto p = chassis.getPose();
            newScreen.print(0, "X: %f", (p.x));
            newScreen.print(1, "Y: %f", (p.y));
            newScreen.print(2, "Theta: %f", (p.theta));
			newScreen.print(3, "Color Sensor Prox: %d", ringColor.get_proximity());
			newScreen.print(4, "Color Sort Enabled: %s", Intake.enableSort ? "Yes" : "No");
			newScreen.print(5, "Keep %s Rings", Intake.getSortColor().c_str());
            pros::delay(10);
        }
    });
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}
/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

void autonomous() {
	float startTime = pros::millis();
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
	// mySelector.run_auton();
	// soloAWPFull();
	ringSideMiddle();
	float endTime = pros::millis();
    float totalTime = endTime - startTime;
    std::cout << totalTime << std::endl;
    master.print(0,0,"%f", totalTime);
}

void opcontrol() {
	while (true) {
		// ez_template_extras();
		mogoControl();
		doinkerControl();
		driveControl();
		controlsManager.checkAndRestartTasks();				 
		pros::delay(20);
	}
}