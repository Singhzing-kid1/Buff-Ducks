#include "main.h"

using namespace std;
using namespace pros;
using namespace lemlib;

Drivetrain_t tanktrain {
    &leftMotorGroup, // left drivetrain motors
    &rightMotorGroup, // right drivetrain motors
    12.75, // track width
    3.25, // wheel diameter
    360 // wheel rpm
};

TrackingWheel leftTrackingWheel (&leftMotorGroup, 3.25, -6.375, 360);
TrackingWheel rightTrackingWheel (&rightMotorGroup, 3.25, 6.375, 360);

OdomSensors_t sensors{
    &leftTrackingWheel,
    &rightTrackingWheel,
    nullptr,
    nullptr,
    nullptr
};

ChassisController_t lateralController{
    8, // kP
    30, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    5 // slew rate
};

ChassisController_t angularController{
    4, // kP
    40, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    40 // slew rate
};

Chassis wheelThingyWithTracking (tanktrain, lateralController, angularController, sensors);