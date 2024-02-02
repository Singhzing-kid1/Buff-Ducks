#include "main.h"

using namespace std;
using namespace pros;
using namespace lemlib;

Drivetrain tanktrain(
    &leftMotorGroup, // left drivetrain motors
    &rightMotorGroup, // right drivetrain motors
    12.75, // track width
    Omniwheel::NEW_325, // wheel diameter
    360, // wheel rpm
    2 //chase power. How fast the robot can corner
);

OdomSensors sensors(
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr
);

ControllerSettings linearController(
                                    10.0, // proportional gain (kP)
                                    0.0,
                                    30.0, // derivative gain (kD)
                                    0.0,
                                    1.0, // small error range, in inches
                                    100.0, // small error range timeout, in milliseconds
                                    3.0, // large error range, in inches
                                    500.0, // large error range timeout, in milliseconds
                                    20.0 // maximum acceleration (slew)
);

ControllerSettings angularController(
                                    2.0, // proportional gain (kP)
                                    0.0,
                                    10.0, // derivative gain (kD)
                                    0.0,
                                    1.0, // small error range, in degrees
                                    100.0, // small error range timeout, in milliseconds
                                    3.0, // large error range, in degrees
                                    500.0, // large error range timeout, in milliseconds
                                    0.0 // maximum acceleration (slew). 0 means no limit
);

Chassis chassis (tanktrain, linearController, angularController, sensors);