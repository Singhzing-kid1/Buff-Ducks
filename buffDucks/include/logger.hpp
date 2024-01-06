#include "main.h"

using namespace std;
using namespace pros;

#pragma once

namespace vLoggger{
    enum class level{FATAL, ERROR, WARN, INFO};

    /**
     * @brief determines the level of the logging line
     * 
     * @param leftMotors left motor group
     * @param rightMotors right motor group
     * @param controller the master controller
     * 
     * @note fatal = battery less than 10%, motor disconnects(any), motor over cirt temp(any), controller disconnect 
     * @note error = battery less than 25% more than 10%, motor over 50 under crit temp   
     * @note warn = batt less than 50% more than 25%, motor 45 - 50 temp   
     * 
     * @return level::FATAL, level::ERROR, level::WARN, or level::INFO 
    */
    level determineLevel(Motor_Group, Motor_Group, Controller);

    /**
     * @brief creates a string that contains all valued variables
     * 
     * @param leftMotors the left motors
     * @param rightMotors the right motors
     * @param controller the master controller
     * @param time the current runtime time
     * 
     * @note the order of the variables is:
     * @note ti, t1, t2, t3, t4, t5, t6, e1, e2, e3, e4, e5, e6, a1, a2, A1, A2, d1, d2, D1, D2, cb, b
     * @note it starts with time, then motors right through left, then analog inputs left through right, digital inputs left through right and finally controller bat level and main bat level
     * 
     * @return string stream
    */
    ostringstream formulateDataString(Motor_Group, Motor_Group, Controller, uint32_t);

    /**
     * @brief creates a log file
     * 
     * @param filename the filename of the log file 
     * 
     * @return ofstream to be passed to other logging functions
    */
    ofstream createLogFile(string);

    /**
     * @brief write line to logging file
     * 
     * @param file the ofstream object
     * @param data  the data (duh)
     * @param logLevel FATAL, ERROR, WARN or INFO
     * 
     * @note appends the log level to the front of the data
     * @note writes the level + data to the file
    */
    void writeLine(ofstream, ostringstream, level);
}

namespace vLogHelpers{

    enum class controlMode{AUTON, OP};

    /**
     * @brief checks if a value is in a determined range
     * 
     * @param value the value
     * @param min minimum value of range
     * @param max maximum value of range
     * 
     * @note checks if the value is between the min and max and not if the value is @ the min or the max
     * 
     * @return true if the value is in the range, false if it is not
    */
    bool isInRange(int, int, int);

    /**
     * @brief intializes stuff for logging
     * 
     * @note literally runs cout.sync_with_stdio(false) to speed up cpp streams.
    */
    void initializeLogging();

    /**
     * @brief uses a random gen to create a unique filename for the logs
     * 
     * @param mode the control period that is being logged
     * @param length length of the random part of the filename
     * 
     * @return a string that is the file name
     * 
     * @note after creating the random gen filename it is appended by either .auton or .operator
     * @note then it is appended by .log
    */
    string uniqueLogName(controlMode, size_t);

    /**
     * @brief gets the vex v5 brain battery percentage at a certain voltage
     * 
     * @param voltage the voltage of the battery
     * 
     * @note uses the formula (voltage - minVoltage) / (maxVoltage - minVoltage) * 100
     * 
     * @return a percentage
     * 
    */
    double getBatteryPercent(double);
}