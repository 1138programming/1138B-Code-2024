#pragma once
#include "EZ-Template/drive/drive.hpp"
#include "api.h"
#include "EZ-Template/api.hpp"

// motors

// sensors
inline ez::tracking_wheel horiz_tracker(8, 2.75, 0.3125);  // This tracking wheel is perpendicular to the drive wheels
// distance is 0.3125 from bot center, 1.8125 from turning center 


inline ez::Drive chassis(
    {20, -19, -18},
    {-16, 17, 21},
    13,
    2.75,
    450
);
