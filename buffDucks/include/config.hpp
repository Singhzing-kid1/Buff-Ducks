#include "main.h"

using namespace std;
using namespace pros;

typedef struct settings{
    int deadZoneLimit = 27;
    int clampLimit = 100;
    int32_t acclerationInterval = (int32_t)3;
    int intakeSpeed = 127;
} driverSettings;

extern vector<driverSettings> drivers;

extern int driverIndex;
extern bool nonDefaultDriver;