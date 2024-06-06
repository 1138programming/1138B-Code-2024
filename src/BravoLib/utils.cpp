#include "BravoLib/utils.h"
#include "math.h"
namespace BravoLib {
    double clamp(double value, double min, double max) {
        if (value < min) return min;
        if (value > max) return max;
        return value;
    }
    // Convert radians to degrees
    double radiansToDegrees(double radians) {
        return radians * (180.0 / M_PI);
    }
    // Convert degrees to radians
    double degreesToRadians(double degrees) {
        return degrees * (M_PI / 180.0);
    }
}