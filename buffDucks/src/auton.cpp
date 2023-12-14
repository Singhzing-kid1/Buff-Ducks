#include "main.h"

using namespace std;
using namespace pros;

const double kP = 0.1;
const double kI = 0.01;
const double kD = 0.05;

double error(double target, double current){
    return target - current;
}

