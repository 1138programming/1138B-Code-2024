#include "screenClass.hpp"
#include "autos.hpp"
#include "systems/intake.hpp"
#include "systems/drive.hpp"
#include "systems/arm.hpp"


inline Screen newScreen(
{{&soloAWPFullBlue, "Signature Event Solo AWP"},{&ringSideMiddleBlue, "7 Ring + Ladder - Ring Side"}}, 
{{&soloAWPFullRed, "Signature Event Solo AWP"}, {&ringSideMiddleRed, "7 Ring + Ladder - Ring Side"}, {&stateSkills, "Skills"}}, 
{{"Left Front", left_motors.get_port(0)}, {"Left Mid", left_motors.get_port(1)}, {"Left Back", left_motors.get_port(2)}, 
{"Right Front", right_motors.get_port(0)}, {"Right Mid", right_motors.get_port(1)},{"Right Back", right_motors.get_port(2)},
{"Intake", intake1.get_port()}, {"Arm 1", armMotor1.get_port()}, {"Arm2", armMotor2.get_port()}});