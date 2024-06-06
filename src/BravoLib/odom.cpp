#include "BravoLib/odom.h"

namespace BravoLib {
    // Constructor with rotation sensor
TrackingWheel::TrackingWheel(pros::Rotation *rotation, float wheelDiameter, float distance, float gearRatio)
    : rotation(rotation), diameter(wheelDiameter), distance(distance), gearRatio(gearRatio) {}

// Constructor with motor group
TrackingWheel::TrackingWheel(pros::Motor *motor, float wheelDiameter, float distance, float rpm)
    : motor(motor), diameter(wheelDiameter), distance(distance), rpm(rpm) {
    motor->set_encoder_units(pros::E_MOTOR_ENCODER_ROTATIONS);
}
// Get the distance delta or the change in distance
float TrackingWheel::getDistanceDelta(bool update) {
    const float prevAngle = this->lastAngle;
    const float angle = this->motor->get();
    if (!update) this->lastAngle = prevAngle;
    return (angle - prevAngle) / 2 * this->diameter;
}
}