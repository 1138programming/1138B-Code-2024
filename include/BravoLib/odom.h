#include "pros/motors.hpp"
#include "pros/rotation.hpp"

namespace BravoLib {

// Robot state structure
struct RobotState {
    double x; // Robot's x-coordinate
    double y; // Robot's y-coordinate
    double theta; // Robot's orientation (in radians)
};

class TrackingWheel {
    public:

        /**
         * @brief Constructor for a tracking wheel with a Rotation sensor.
         * @param rotation Pointer to the Rotation object.
         * @param wheelDiameter Diameter of the wheel in meters.
         * @param distance Wheel offset from the robot center in meters.
         * @param gearRatio Gear ratio of the wheel (encoder/motor).
         */
        TrackingWheel(pros::Rotation *rotation, float wheelDiameter, float distance, float gearRatio = 1.0f);

        /**
         * @brief Constructor for a tracking wheel with a MotorGroup.
         * @param motors Pointer to the MotorGroup object.
         * @param wheelDiameter Diameter of the wheel in meters.
         * @param distance Wheel offset from the robot center in meters.
         * @param rpm RPM of the motor group.
         */
        TrackingWheel(pros::Motor *motor, float wheelDiameter, float distance, float rpm);

        /**
         * @brief Gets the distance delta or the change in distance.
         * @param update Whether to update the distance delta or not (default: true).
         * @return The distance delta or change in distance in meters.
         */
        float getDistanceDelta(bool update = true);
    private:
        std::unique_ptr<pros::Rotation> rotation;   // Pointer to rotation sensor (optional)
        std::unique_ptr<pros::Motor> motor;         // Pointer to motor group (optional)
        float diameter;                             // Wheel diameter in meters
        float distance;                             // Wheel offset from the robot center in meters
        float gearRatio;                            // Gear ratio of the wheel (encoder/motor)
        float rpm;                                  // RPM of the motor group (optional)
        float lastAngle = 0;                        // Last angle of the wheel
};

class Odometry {
private:
    double sL; // Distance from tracking center to the left tracking wheel
    double sR; // Distance from tracking center to the right tracking wheel
    double prevLeftEncoder, prevRightEncoder;
    double x, y, theta; // Robot's current x, y position and orientation in radians


public:
    Odometry(double sL, double sR, double sS);

    void update(double leftEncoder, double rightEncoder, double backEncoder);

    double getX() const { return x; }
    double getY() const { return y; }
    double getTheta() const { return theta; }
};



}
