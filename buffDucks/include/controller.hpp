#include "main.h"

using namespace std;
using namespace pros;

extern Controller master;

bool isInside(int32_t, int32_t, int32_t);

int32_t deadzone(controller_analog_e_t, controller_analog_e_t);

bool closeEnough(int32_t, int32_t);