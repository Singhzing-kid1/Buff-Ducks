#include "main.h"

using namespace std;
using namespace pros;

extern Controller master;

/**
 *@brief calculates wether the inputs are in or outside a circular deadzone
 *
 * @param valueX X analog value
 * @param valueY Y analog value
 * 
 * @return either zero, the hypotenuse of the inputs, or just the Y analog input 
*/
int32_t deadzone(controller_analog_e_t, controller_analog_e_t);

/**
 * @brief checks if a point is inside a circle
 * 
 * @param x x coord
 * @param y y coord
 * @param rad radius of circle to check inside of
 * 
 * @return returns true if the hypotenuse(+ or -) of the coord pair (x, y) is less than the radius
*/
bool isInside(int32_t, int32_t, int);

/**
 * @brief checks if two inputs are near each other
 * 
 * @param rightSpeed right speed input
 * @param leftSpeed left speed input
 * 
 * @return true if the diff between both inputs is less than or equal to five
*/
bool closeEnough(int32_t, int32_t);