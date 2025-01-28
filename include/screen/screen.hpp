#include "screenClass.hpp"
#include "autos.hpp"
#include "systems/intake.hpp"
#include "systems/drive.hpp"
#include "systems/arm.hpp"


inline Screen newScreen(
{{&soloAWPFull, "Signature Event Solo AWP"}}, 
{{&ringSideMiddle, "6 Ring - Ring Side"}}, 
{{"Left", &left_motors}, {"Right", &right_motors}, {"Intake", &intake1}, {"Arm 1", &armMotor1}, {"Arm2", &armMotor2}});