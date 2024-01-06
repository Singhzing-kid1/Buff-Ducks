#include "main.h"

using namespace std;
using namespace pros;
using namespace vLoggger;
using namespace vLogHelpers;

namespace vLogger{

    level determineLevel(Motor_Group leftMotors, Motor_Group rightMotors, Controller controller){
        //FATAL CLAUSE

        vector<int32_t> areLeftTempsOver = leftMotors.are_over_temp();
        vector<int32_t> areRightTempsOver = rightMotors.are_over_temp();

        int fatalVal = 1;

        if(any_of(areLeftTempsOver.begin(), areLeftTempsOver.end(), [fatalVal](int i){return i == fatalVal;}) || any_of(areRightTempsOver.begin(), areRightTempsOver.end(), [fatalVal](int i){return i == fatalVal;}) || any_of(areLeftTempsOver.begin(), areLeftTempsOver.end(), [](int i){return i == ENODEV;}) || any_of(areRightTempsOver.begin(), areRightTempsOver.end(), [](int i){ return i == ENODEV;}) || getBatteryPercent(battery::get_capacity()) <= 10 || controller.is_connected() ==0){
            return level::FATAL;
        }

        //ERROR CLAUSE

        vector<double> currentLeftTemps = leftMotors.get_temperatures();
        vector<double> currentRightTemps = rightMotors.get_temperatures();

        int minErrTemp = 50;
        int minErrBat = 11;
        int maxErrBat = 25;

        if(any_of(currentLeftTemps.begin(), currentLeftTemps.end(), [minErrTemp](int i){return i >= minErrTemp;}) || any_of(currentRightTemps.begin(), currentRightTemps.end(), [minErrTemp](int i){return i >= minErrTemp;}) || isInRange(getBatteryPercent(battery::get_capacity()), minErrBat, maxErrBat)){
            return level::ERROR;
        }

        //WARN CLAUSE

        int minWarnTemp = 44;
        int maxWarnTemp = 50;
        int minWarnBat = 25;
        int maxWarnBat = 50;

        if(any_of(currentLeftTemps.begin(), currentLeftTemps.end(), [minWarnTemp, maxWarnTemp](int i){return isInRange(i, minWarnTemp, maxWarnTemp);}) || any_of(currentRightTemps.begin(), currentRightTemps.end(), [minWarnTemp, maxWarnTemp](int i){return isInRange(i, minWarnTemp, maxWarnTemp);}) || isInRange(getBatteryPercent(battery::get_capacity()), minWarnBat, maxWarnBat)){
            return level::WARN;
        }

        return level::INFO;
    }

    ostringstream formulateDataString(Motor_Group leftMotors, Motor_Group rightMotors, Controller controller, uint32_t time){
        ostringstream dataStream;
        ostringstream motorTemps;
        ostringstream motorEncoders;
        ostringstream analogIns;
        ostringstream digitalIns;
        ostringstream batteries;

        motorTemps << rightMotors[0].get_temperature() << ", " << rightMotors[1].get_temperature() << ", " << rightMotors[2].get_temperature() << ", " << leftMotors[0].get_temperature() << ", " << leftMotors[1].get_temperature() << ", " << leftMotors[2].get_temperature() << ", ";
        motorEncoders << rightMotors[0].get_position() << ", " << rightMotors[1].get_position() << ", " << rightMotors[2].get_position() << ", " << leftMotors[0].get_position() << ", " << leftMotors[1].get_position() << ", " << leftMotors[2].get_position() << ", ";
        analogIns << controller.get_analog(ANALOG_LEFT_Y) << ", " << controller.get_analog(ANALOG_LEFT_X) << ", " << controller.get_analog(ANALOG_RIGHT_Y) << ", " << controller.get_analog(ANALOG_RIGHT_X) << ", ";
        digitalIns << controller.get_digital(DIGITAL_L1) << ", " << controller.get_digital(DIGITAL_L2) << ", " << controller.get_digital(DIGITAL_R1) << ", " << controller.get_digital(DIGITAL_R2) << ", ";
        batteries << controller.get_battery_level() << ", " << getBatteryPercent(battery::get_capacity()) << endl;

        dataStream << time << ", " << motorTemps.str() << motorEncoders.str() << analogIns.str() << digitalIns.str() << batteries.str();

        return dataStream;
        // ti, t1, t2, t3, t4, t5, t6, e1, e2, e3, e4, e5, e6, a1, a2, A1, A2, d1, d2, D1, D2, cb, b 
    }

    ofstream createLogFile(string fileName){
        ofstream logFile("/usd/" + fileName + ".txt");

        return logFile;
    }

    void writeLine(ofstream file, ostringstream data, level logLevel){
        ostringstream levelString;

        switch(logLevel){
            case level::FATAL:
                levelString << "FATAL, ";
                break;

            case level::ERROR:
                levelString << "ERROR, ";
                break;
            
            case level::WARN:
                levelString << "WARN, ";
                break;

            default:
                levelString << "INFO, ";
                break;
        }

        file << levelString.str() << data.str();
    }
}

namespace vLogHelpers{
    bool isInRange(int value, int min, int max){
        return (value > min && max < value);
    }

    void initializeLogging(){
        cout.sync_with_stdio(false);
    }

    string uniqueLogName(controlMode mode, size_t length){
        const string CHARACTERS = "0123456789qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";

        random_device randomDevice;
        mt19937 generator(randomDevice());
        uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

        string logName;

        for(size_t i; i < length; i++){
            logName += CHARACTERS[distribution(generator)];
        }

        switch(mode){
            case controlMode::AUTON:
                logName += ".auton";
                break;

            case controlMode::OP:
                logName += ".operator";
                break;
        }

        logName += ".log";

        return logName;
    }

    double getBatteryPercent(double voltage){
        double minVoltage = 10.0;
        double maxVoltage = 14.6;

        return (voltage - minVoltage) / (maxVoltage - minVoltage) * 100.0;
    }
}