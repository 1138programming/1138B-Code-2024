#include "pros/motors.hpp"
#include <string>

namespace BravoLib {


struct NamedMotor {
    pros::Motor motor;
    std::string name;

    NamedMotor(pros::Motor motor, std::string name) : motor(motor), name(name) {}
};

class MotorDevices {
public:
    std::vector<NamedMotor> motors;

    MotorDevices(std::initializer_list<NamedMotor> motorList) : motors(motorList) {}
};

}