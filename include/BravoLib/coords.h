#pragma once


/**
 * @brief Represents a coordinate in 2D space.
 */
class Coord {
    public:
        float x, y;

        /**
         * @brief Constructs a Coord object with the given x and y coordinates.
         * @param x The x coordinate.
         * @param y The y coordinate.
         */
        Coord(float x, float y) : x(x), y(y) {}
};

