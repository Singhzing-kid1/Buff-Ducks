#include "main.h"

using namespace std;
using namespace pros;

#pragma once

namespace duckTrace{
    enum class level{FATAL, ERROR, WARN, INFO};

    level determineLevel(vector<Motor>, vector<Motor>, Controller);

    ostringstream formulateDataString(vector<Motor>, vector<Motor>, Controller, uint32_t);

    fstream createLogFile(string);

    void writeLine(fstream*, ostringstream*, level);
}

namespace duckTraceHelper{
    enum class controlMode{AUTON, OPERATOR, OPSKILLS, AUTONSKILLS, PIT};

    extern fstream ruleFile;

    bool isInRange(int, int, int);

    double getBatteryPercent(double);

    fstream initializeLogging();

    void closeAndUpdateRuleFile(fstream*);

    string uniqueLogName(controlMode, fstream*);
}