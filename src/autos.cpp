#include "api.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "robodash/views/selector.hpp"
#include "systems/classes.hpp"
#include "systems/drive.hpp"
#include "robodash/api.h"
#include "systems/mogo.hpp"
#include "systems/intake.hpp"
#include "systems/doinker.hpp"
#include "autos.hpp"
#include "systems/controlscheme.hpp"
#include "systems/arm.hpp"

void default_constants() {
  // P, I, D, and Start I
  chassis.pid_drive_constants_set(20.0, 0.0, 100.0);         // Fwd/rev constants, used for odom and non odom motions
  chassis.pid_heading_constants_set(11.0, 0.0, 20.0);        // Holds the robot straight while going forward without odom
  chassis.pid_turn_constants_set(3.0, 0.05, 20.0, 15.0);     // Turn in place constants
  chassis.pid_swing_constants_set(6.0, 0.0, 65.0);           // Swing constants
  chassis.pid_odom_angular_constants_set(6.5, 0.0, 52.5);    // Angular control for odom motions
  chassis.pid_odom_boomerang_constants_set(5.8, 0.0, 32.5);  // Angular control for boomerang motions
  // . . .
}