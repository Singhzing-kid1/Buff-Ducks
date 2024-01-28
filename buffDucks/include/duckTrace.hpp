#include "main.h"

using namespace std;
using namespace pros;

#pragma once

namespace duckTrace{
    ostringstream formulateDataString(vector<Motor>, vector<Motor>, Controller, uint32_t);

    fstream createLogFile(string);

    void writeLine(fstream*, ostringstream*);
}

namespace duckTraceHelper{
    enum class controlMode{AUTON, OPERATOR, OPSKILLS, AUTONSKILLS, PIT};

    extern fstream ruleFile;

    bool isInRange(int, int, int);

    double getBatteryPercent(double);

    fstream initializeLogging();

    void closeAndUpdateRuleFile(fstream*);

    string uniqueLogName(fstream*, controlMode);
}