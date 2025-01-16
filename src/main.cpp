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
	pros::lcd::initialize();
	chassis.odom_tracker_front_set(&horiz_tracker);

	// Set the drive to your own constants from autons.cpp!
  	default_constants();

	// These are already defaulted to these buttons, but you can change the left/right curve buttons here!
	// chassis.opcontrol_curve_buttons_left_set(pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT);  // If using tank, only the left side is used.
	// chassis.opcontrol_curve_buttons_right_set(pros::E_CONTROLLER_DIGITAL_Y, pros::E_CONTROLLER_DIGITAL_A);

	// Autonomous Selector using LLEMU
	ez::as::auton_selector.autons_add({
		{"Drive\n\nDrive forward and come back", drive_example},
		{"Turn\n\nTurn 3 times.", turn_example},
		{"Drive and Turn\n\nDrive forward, turn, come back", drive_and_turn},
		{"Drive and Turn\n\nSlow down during drive", wait_until_change_speed},
		{"Swing Turn\n\nSwing in an 'S' curve", swing_example},
		{"Motion Chaining\n\nDrive forward, turn, and come back, but blend everything together :D", motion_chaining},
		{"Combine all 3 movements", combining_movements},
		{"Interference\n\nAfter driving forward, robot performs differently if interfered or not", interfered_example},
		{"Simple Odom\n\nThis is the same as the drive example, but it uses odom instead!", odom_drive_example},
		{"Pure Pursuit\n\nGo to (0, 30) and pass through (6, 10) on the way.  Come back to (0, 0)", odom_pure_pursuit_example},
		{"Pure Pursuit Wait Until\n\nGo to (24, 24) but start running an intake once the robot passes (12, 24)", odom_pure_pursuit_wait_until_example},
		{"Boomerang\n\nGo to (0, 24, 45) then come back to (0, 0, 0)", odom_boomerang_example},
		{"Boomerang Pure Pursuit\n\nGo to (0, 24, 45) on the way to (24, 24) then come back to (0, 0, 0)", odom_boomerang_injected_pure_pursuit_example},
		{"Measure Offsets\n\nThis will turn the robot a bunch of times and calculate your offsets for your tracking wheels.", measure_offsets},
	});

	// Initialize chassis and auton selector
	chassis.initialize();
	ez::as::initialize();
	master.rumble(chassis.drive_imu_calibrated() ? "." : "---");

	Intake.setSpeed(600);
	arm.setBrakeMode(MOTOR_BRAKE_HOLD);
	Intake.setSortColor(pros::Color::red);
	initilizeControls();
	//pros::lcd::set_text(1, "Hello PROS User!");
	//pros::lcd::register_btn1_cb(on_center_button);
	//mySelector.focus();
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
	chassis.pid_targets_reset();                // Resets PID targets to 0
  	chassis.drive_imu_reset();                  // Reset gyro position to 0
 	chassis.drive_sensor_reset();               // Reset drive sensors to 0
  	chassis.odom_xyt_set(0_in, 0_in, 0_deg);    // Set the current position, you can start at a specific position with this
  	chassis.drive_brake_set(MOTOR_BRAKE_HOLD);  // Set motors to hold.  This helps autonomous consistency
	ez::as::auton_selector.selected_auton_call();  // Calls selected auton from autonomous selector
	float endTime = pros::millis();
    float totalTime = endTime - startTime;
    std::cout << totalTime << std::endl;
    master.print(0,0,"%f", totalTime);
}

/**
 * Simplifies printing tracker values to the brain screen
 */
void screen_print_tracker(ez::tracking_wheel *tracker, std::string name, int line) {
  std::string tracker_value = "", tracker_width = "";
  // Check if the tracker exists
  if (tracker != nullptr) {
    tracker_value = name + " tracker: " + util::to_string_with_precision(tracker->get());             // Make text for the tracker value
    tracker_width = "  width: " + util::to_string_with_precision(tracker->distance_to_center_get());  // Make text for the distance to center
  }
  ez::screen_print(tracker_value + tracker_width, line);  // Print final tracker text
}

/**
 * Ez screen task
 * Adding new pages here will let you view them during user control or autonomous
 * and will help you debug problems you're having
 */
void ez_screen_task() {
  while (true) {
    // Only run this when not connected to a competition switch
    if (!pros::competition::is_connected()) {
      // Blank page for odom debugging
      if (chassis.odom_enabled() && !chassis.pid_tuner_enabled()) {
        // If we're on the first blank page...
        if (ez::as::page_blank_is_on(0)) {
          // Display X, Y, and Theta
          ez::screen_print("x: " + util::to_string_with_precision(chassis.odom_x_get()) +
                               "\ny: " + util::to_string_with_precision(chassis.odom_y_get()) +
                               "\na: " + util::to_string_with_precision(chassis.odom_theta_get()),
                           1);  // Don't override the top Page line

          // Display all trackers that are being used
          screen_print_tracker(chassis.odom_tracker_left, "l", 4);
          screen_print_tracker(chassis.odom_tracker_right, "r", 5);
          screen_print_tracker(chassis.odom_tracker_back, "b", 6);
          screen_print_tracker(chassis.odom_tracker_front, "f", 7);
        }
      }
    }

    // Remove all blank pages when connected to a comp switch
    else {
      if (ez::as::page_blank_amount() > 0)
        ez::as::page_blank_remove_all();
    }

    pros::delay(ez::util::DELAY_TIME);
  }
}
pros::Task ezScreenTask(ez_screen_task);


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