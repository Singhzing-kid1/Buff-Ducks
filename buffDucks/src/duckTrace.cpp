#include "main.h"

using namespace std;
using namespace pros;
using namespace duckTrace;
using namespace duckTraceHelper;

namespace duckTrace{

    ostringstream formulateDataString(vector<Motor> leftMotors, vector<Motor> rightMotors, Controller controller, uint32_t time, vector<Motor>* optionalMotors = nullptr){
        ostringstream dataStream;
        ostringstream motorTemps;
        ostringstream motorEncoders;
        ostringstream optionalMotorTemps;
        ostringstream optionalMotorEnocders;
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

        for(const auto& obj : *optionalMotors){
            optionalMotorTemps << obj.get_temperature() << ", ";
            optionalMotorEnocders << obj.get_position() << ", ";
            
        }

        analogIns << controller.get_analog(ANALOG_LEFT_Y) << ", " << controller.get_analog(ANALOG_LEFT_X) << ", " << controller.get_analog(ANALOG_RIGHT_Y) << ", " << controller.get_analog(ANALOG_RIGHT_X) << ", ";
        digitalIns << controller.get_digital(DIGITAL_L1) << ", " << controller.get_digital(DIGITAL_L2) << ", " << controller.get_digital(DIGITAL_R1) << ", " << controller.get_digital(DIGITAL_R2) << ", " << controller.get_digital(DIGITAL_A) << ", " << controller.get_digital(DIGITAL_Y) << ", ";
        batteries << controller.get_battery_level() << ", " << battery::get_capacity() << endl;

        dataStream << time << motorTemps.str() << motorEncoders.str() << optionalMotorTemps.str() << optionalMotorEnocders.str() << analogIns.str() << digitalIns.str() << batteries.str();

        return dataStream;

        // ti, tR1, tR2, ... , tRn, tL1, tL2, ..., tLn, eR1, eR2, ... , eRn, eL1, eL2, ... , eLn, oT1, oT2, ... , oTn, oE1, oE2, ... , oEn, aLy, aLx, aRy, aRx, dL1, dL2, dR1, dR2, dA, dY, cb, b
    }

    fstream createLogFile(string fileName){
        fstream logFile("/usd/" + fileName + ".txt", ios::out);

        return logFile;
    }

    void writeLine(fstream* file, ostringstream* data){
        *file << data->str();
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

    string uniqueLogName(fstream* logNameRuleFile, controlMode mode = controlMode::PIT){
        string competition, match, logName;

        getline(*logNameRuleFile, competition);
        getline(*logNameRuleFile, match);

        logName += competition;
        logName += match;  

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

            case controlMode::PIT:
                logName += ".pit";
                break;
        }

        logName += ".log";

        return logName;
    }

    void closeAndUpdateRuleFile(fstream* logNameRuleFile){
        int matchNum;
        string bufferString;

        istringstream buffer;

        getline(*logNameRuleFile, bufferString);
        streampos pos = logNameRuleFile->tellg();
        getline(*logNameRuleFile, bufferString);

        logNameRuleFile->seekg(pos);

        buffer.str("");
        buffer.str(bufferString);

        buffer >> matchNum;

        matchNum += 1;

        *logNameRuleFile << matchNum << "\n";

        logNameRuleFile->close();
    }

}

