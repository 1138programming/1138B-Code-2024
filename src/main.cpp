#include "main.h"
#include "liblvgl/llemu.hpp"
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
	{"Red Goal Side", &localAWPGoalRed},
	{"Blue Goal Side", &localAWPGoalBlue}
});

TaskWrapper intakeControlThread(intakeControl, nullptr, "Intake Control");
TaskWrapper armControlThread(armControl, nullptr, "Arm Control");

TaskManager controlsManager;

void sortRed() {
	Intake.setSortColor(pros::Color::red);
}

void sortBlue() {
	Intake.setSortColor(pros::Color::blue);
}

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

	pros::lcd::initialize();
	pros::lcd::register_btn0_cb(sortRed);
	pros::lcd::register_btn1_cb(sortBlue);
	// Initialize chassis and auton selector
	chassis.calibrate();

	Intake.setSpeed(600);
	arm.setBrakeMode(MOTOR_BRAKE_HOLD);
	Intake.setSortColor(pros::Color::red);
	initilizeControls();
	armMotor1.tare_position();
	armMotor2.tare_position();
	ringColor.set_integration_time(10);
	pros::Task([&] {
        while (true) {
            auto p = chassis.getPose();
            pros::lcd::print(0, "X: %f", (p.x));
            pros::lcd::print(1, "Y: %f", (p.y));
            pros::lcd::print(2, "Theta: %f", (p.theta));
			pros::lcd::print(3, "Color Sensor Prox: %d", ringColor.get_proximity());
			pros::lcd::print(4, "%d", Intake.currentRingColor);
			pros::lcd::print(5, "R: %d, G: %d, B: %d, C: %d", ringColor.get_raw().red, ringColor.get_raw().green, ringColor.get_raw().blue, ringColor.get_raw().clear);
            pros::delay(10);
        }
    });
	// // chassis.pid_tuner_enable();
	//pros::lcd::set_text(1, "Hello PROS User!");
	//pros::lcd::register_btn1_cb(on_center_button);
	// mySelector.focus();
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
		pros::lcd::print(0, "%d", (int)Intake.currentRingColor);
		pros::delay(20);
	}
}