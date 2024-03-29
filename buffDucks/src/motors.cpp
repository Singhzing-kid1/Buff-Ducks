#include "main.h"

using namespace std;
using namespace pros;

Motor leftMotor1(11, E_MOTOR_GEAR_BLUE, false);
Motor leftMotor2(12, E_MOTOR_GEAR_BLUE, false);
Motor leftMotor3(13, E_MOTOR_GEAR_BLUE, false);

Motor rightMotor1(14, E_MOTOR_GEAR_BLUE, true);
Motor rightMotor2(15, E_MOTOR_GEAR_BLUE, true);
Motor rightMotor3(16, E_MOTOR_GEAR_BLUE, true);

Motor intakeMotor(17, E_MOTOR_GEAR_BLUE, false);

Motor_Group leftMotorGroup({leftMotor1, leftMotor2, leftMotor3});
Motor_Group rightMotorGroup({rightMotor1, rightMotor2, rightMotor3});

int32_t accelerate(int32_t newSpeed, int32_t oldSpeed){
    if(newSpeed > oldSpeed){
        return oldSpeed += 20;
    } else if (newSpeed < oldSpeed){
        return oldSpeed -= 20;
    } else {
        return oldSpeed;
    }
}