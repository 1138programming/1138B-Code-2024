#include "regression.h"
#include "functions.h"

// Constructor for the Regression class
Regression::Regression(std::vector<Coord> points) : points(points) {}

// Function to calculate the dot product of two vectors
double Regression::dotProduct(const std::vector<double> &v1, const std::vector<double> &v2) {
    double product = 0.0;
    for (int i = 0; i < v1.size(); i++) { product += v1[i] * v2[i]; }
    return product;
}

// Function to fit a function through the coordinates using ridge regression
std::pair<double, double> Regression::Ridge() {
    std::vector<double> x(this->points.size());
    std::vector<double> y(this->points.size());

    for (int i = 0; i < points.size(); i++) {
        x[i] = points[i].x;
        y[i] = points[i].y;
    }

    double xMean = avg(x);
    double yMean = avg(y);

    double xDotY = this->dotProduct(x, y);
    double xDotX = this->dotProduct(x, x);
    double n = this->points.size();

    // Calculate lambda as 1% of the sum of squares of x
    lambda = 0.01 * xDotX;

    double m = (xDotY - n * xMean * yMean) / (xDotX - n * xMean * xMean + this->lambda);
    double b = yMean - m * xMean;

    return std::make_pair(m, b);
}

double Regression::predict(double x) {
    std::pair<double, double> coefficients = this->Ridge();
    double m = coefficients.first;
    double b = coefficients.second;
    return m * x + b;
}