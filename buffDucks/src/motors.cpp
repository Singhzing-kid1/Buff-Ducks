#include "main.h"

using namespace std;
using namespace pros;

Motor_Group rightMotorGroup({11, 12, -13});
Motor_Group leftMotorGroup({14, 15, -16});

int32_t accelerate(int32_t newSpeed, int32_t oldSpeed){
    if(newSpeed > oldSpeed){
        return oldSpeed += 5;
    } else if (newSpeed < oldSpeed){
        return oldSpeed -= 5;
    } else {
        return oldSpeed;
    }
}