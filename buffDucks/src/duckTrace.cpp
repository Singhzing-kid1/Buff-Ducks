#include "main.h"

using namespace std;
using namespace pros;
using namespace duckTrace;
using namespace duckTraceHelper;

namespace duckTrace{
    level determineLevel(vector<Motor> leftMotors, vector<Motor> rightMotors, Controller controller){
        // FATAL CLAUSE

        vector<int32_t> areLeftTempsOver;
        vector<int32_t> areRightTempsOver;

        int32_t fatalVal = 1;

        for(const auto& obj : leftMotors){
            areLeftTempsOver.push_back(obj.is_over_temp());
        }

        for(const auto& obj : rightMotors){
            areLeftTempsOver.push_back(obj.is_over_temp());
        }

        if(any_of(areLeftTempsOver.begin(), areLeftTempsOver.end(), [fatalVal](int32_t x){return x == fatalVal;}) || any_of(areRightTempsOver.begin(), areRightTempsOver.end(), [fatalVal](int32_t x){return x == fatalVal;}) || any_of(areLeftTempsOver.begin(), areLeftTempsOver.end(), [](int x){return x == ENODEV;}) || any_of(areRightTempsOver.begin(), areRightTempsOver.end(), [](int x){return x == ENODEV;}) || getBatteryPercent(battery::get_capacity()) <= 10 || controller.is_connected() == 0){
            return level::FATAL;
        }

        //ERROR CLAUSE

        vector<double> leftTemps;
        vector<double> rightTemps;

        int minErrTemp = 50;
        int minErrBat = 10;
        int maxErrBat = 25;

        for(const auto& obj : leftMotors){
            leftTemps.push_back(obj.get_temperature());
        }

        for(const auto& obj : rightMotors){
            rightTemps.push_back(obj.get_temperature());
        }

        if(any_of(leftTemps.begin(), leftTemps.end(), [minErrTemp](int x){return x >= minErrTemp;}) || any_of(rightTemps.begin(), rightTemps.end(), [minErrTemp](int x){return x >= minErrTemp;}) || isInRange(getBatteryPercent(battery::get_capacity()), minErrBat, maxErrBat)){
            return level::ERROR;
        }

        //WARN CLAUSE

        int minWarnTemp = 44;
        int maxWarnTemp = 50;
        int minWarnBat = 25;
        int maxWatnBat = 50;

        if(any_of(leftTemps.begin(), leftTemps.end(), [minWarnTemp, maxWarnTemp](int x){return isInRange(x, minWarnTemp, maxWarnTemp);}) || any_of(rightTemps.begin(), rightTemps.end(), [minWarnTemp, maxWarnTemp](int x){return isInRange(x, minWarnTemp, maxWarnTemp);}) || isInRange(getBatteryPercent(battery::get_capacity()), minWarnBat, maxWatnBat)){
            return level::WARN;
        }

        return level::INFO;
        

    }

    ostringstream formulateDataString(vector<Motor> leftMotors, vector<Motor> rightMotors, Controller controller, uint32_t time){
        ostringstream dataStream;
        ostringstream motorTemps;
        ostringstream motorEncoders;
        ostringstream analogIns;
        ostringstream digitalIns;
        ostringstream batteries;

        for(const auto& obj : rightMotors){
            motorTemps << obj.get_temperature() << ", ";
            motorEncoders << obj.get_position() << ", ";
        }

        for(const auto& obj : leftMotors){
            motorTemps << obj.get_temperature() << ", ";
            motorEncoders << obj.get_position() << ", ";
        }

        analogIns << controller.get_analog(ANALOG_LEFT_Y) << ", " << controller.get_analog(ANALOG_LEFT_X) << ", " << controller.get_analog(ANALOG_RIGHT_Y) << ", " << controller.get_analog(ANALOG_RIGHT_X) << ", ";
        digitalIns << controller.get_digital(DIGITAL_L1) << ", " << controller.get_digital(DIGITAL_L2) << ", " << controller.get_digital(DIGITAL_R1) << ", " << controller.get_digital(DIGITAL_R2) << ", ";
        batteries << controller.get_battery_level() << ", " << getBatteryPercent(battery::get_capacity()) << endl;

        dataStream << time << motorTemps.str() << motorEncoders.str() << analogIns.str() << digitalIns.str() << batteries.str();

        return dataStream;

        // ti, tR1, tR2, ... , tRn, tL1, tL2, ..., tLn, eR1, eR2, ... , eRn, eL1, eL2, ... , eLn, aLy, aLx, aRy, aRx, dL1, dL2, dR1, dR2, cb, b
    }

    fstream createLogFile(string fileName){
        fstream logFile("/usd/" + fileName + ".txt", ios::out);

        return logFile;
    }

    void writeLine(fstream* file, ostringstream* data, level logLevel){
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

        *file << levelString.str() << data->str();
    }
}

namespace duckTraceHelper{

    fstream ruleFile;

    bool isInRange(int value, int min, int max){
        return (value > min && max < value);
    }

    fstream initializeLogging(){
        fstream logNameRuleFile("/usd/logRuleFile.txt");
        return logNameRuleFile;
    }

    string uniqueLogName(controlMode mode = , fstream* logNameRuleFile){
        string competition, match, logName;

        getline(*logNameRuleFile, competition);
        getline(*logNameRuleFile, match);

        logName += competition;
        logName += to_string(stoi(match) + 1);  

        switch(mode){
            case controlMode::AUTON:
                logName += ".auton";
                break;
            
            case controlMode::OPERATOR:
                logName += ".operator";
                break;

            case controlMode::OPSKILLS:
                logName +=".operator.skills";
                break;
            
            case controlMode::AUTONSKILLS:
                logName += ".auton.skills";
                break;

            case default:
                logName += ".pit";
                break;
        }

        logName += ".log";

        return logName;
    }

    void closeAndUpdateRuleFile(fstream* logNameRuleFile){
        int matchNum;
        string buffer;

        getline(*logNameRuleFile, buffer);
        streampos pos = logNameRuleFile->tellg();
        getline(*logNameRuleFile, buffer);

        logNameRuleFile->seekg(pos);
        matchNum = stoi(buffer) + 1;

        *logNameRuleFile << to_string(matchNum) << "\n";

        logNameRuleFile->close();
    }

    double getBatteryPercent(double voltage){
        double minVoltage = 10.0;
        double maxVoltage = 14.6;

        return (voltage - minVoltage)/(maxVoltage - minVoltage) * 100.0;
    }
}

