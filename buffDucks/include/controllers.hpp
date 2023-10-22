using namespace std;
using namespace pros;

extern Controller master;

int32_t deadzone(controller_analog_e_t, controller_analog_e_t);
int32_t clamp(int32_t);
bool tempWarningRumbler(std::string, int, Motor, bool);