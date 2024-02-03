#include "main.h"

using namespace std;
using namespace pros;

#pragma once

namespace duckTrace{
    ostringstream formulateDataString(vector<Motor>, vector<Motor>, Controller, uint32_t, vector<Motor>*);

    fstream createLogFile(string);

    void writeLine(fstream*, ostringstream*);
}

namespace duckTraceHelper{
    enum class controlMode{AUTON, OPERATOR, OPSKILLS, AUTONSKILLS, PIT};

    extern fstream ruleFile;

    fstream initializeLogging();

    void closeAndUpdateRuleFile(fstream*);

    string uniqueLogName(fstream*, controlMode);
}