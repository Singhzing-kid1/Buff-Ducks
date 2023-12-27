#include "main.h"

using namespace std;
using namespace pros;

extern Motor_Group rightMotorGroup;
extern Motor_Group leftMotorGroup;

/**
 *@brief gradually adds to the current speed to get to the desired speed
 *
 * @param newSpeed the desired speed
 * @param currentSpeed current set speed of motors
 * 
 * @return the current speed +/- 5 to get closer to the desired speed 
*/
int32_t accelerate(int32_t, int32_t);