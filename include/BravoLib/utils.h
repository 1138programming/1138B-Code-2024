#include <vector>

namespace BravoLib {

double clamp(double value, double min, double max);
/**
 * @brief Calculates the average of a vector of any type.
 *
 * This function computes the arithmetic mean of a vector of elements of any
 * type.
 *
 * @tparam vec The vector of elements.
 * @return The average value (in any datatype).
 */
template <typename T> T avg(const std::vector<T> &vec) {
    T sum = T();  // Initialize sum to default value for T
    for (const T &elem : vec) { sum += elem; }
    return sum / vec.size();
}
double radiansToDegrees(double radians);
double degreesToRadians(double degrees);
}