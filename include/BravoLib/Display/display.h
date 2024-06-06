#include "BravoLib/Display/motorData.h"
namespace BravoLib {
    class Display {
        private:
            MotorDevices motors;
        public:
            Display(MotorDevices motors_);
            void updateDisplay();
            MotorDevices returnMotors();

    };
}

