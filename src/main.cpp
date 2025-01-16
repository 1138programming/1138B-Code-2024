#include "main.h"
#include "pros/motors.h"
#include "systems/classes.hpp"
#include "systems/drive.hpp"
#include "systems/intake.hpp"
#include "systems/arm.hpp"
#include "systems/controlscheme.hpp"
#include "autos.hpp"
#include "taskmanager/taskmanager.hpp"
#include <cstddef>


rd::Selector mySelector({
});

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
	//pros::lcd::initialize();
	chassis.odom_tracker_front_set(&horiz_tracker);
	chassis.initialize();
	Intake.setSpeed(600);
	arm.setBrakeMode(MOTOR_BRAKE_HOLD);
	Intake.setSortColor(pros::Color::red);
	initilizeControls();
	//pros::lcd::set_text(1, "Hello PROS User!");
	//pros::lcd::register_btn1_cb(on_center_button);
	mySelector.focus();
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
	chassis.drive_brake_set(pros::E_MOTOR_BRAKE_HOLD);
	controlsManager.stopTask(&intakeControlThread);
	//mySelector.run_auton();
	
	float endTime = pros::millis();
    float totalTime = endTime - startTime;
    std::cout << totalTime << std::endl;
    master.print(0,0,"%f", totalTime);
}
/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	controlsManager.startTask(&intakeControlThread);
	while (true) {
		mogoControl();
		doinkerControl();
		driveControl();
		controlsManager.checkAndRestartTasks();				 
		pros::lcd::print(0, "%d", (int)Intake.currentRingColor);
		pros::delay(ez::util::DELAY_TIME);
	}
}