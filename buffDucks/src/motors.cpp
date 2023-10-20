#include "main.h"

using namespace std;
using namespace pros;

Motor leftMotor1 (1, E_MOTOR_GEAR_BLUE, true, E_MOTOR_ENCODER_DEGREES);
Motor leftMotor2 (2, E_MOTOR_GEAR_BLUE, true, E_MOTOR_ENCODER_DEGREES);
Motor leftMotor3 (3, E_MOTOR_GEAR_BLUE, false, E_MOTOR_ENCODER_DEGREES); // We have a motor stack. This is a stacked motor and it needs to be reversed compared to the other motors

Motor rightMotor1 (4, E_MOTOR_GEAR_BLUE, true, E_MOTOR_ENCODER_DEGREES);
Motor rightMotor2 (5, E_MOTOR_GEAR_BLUE, true, E_MOTOR_ENCODER_DEGREES);
Motor rightMotor3 (6, E_MOTOR_GEAR_BLUE, false, E_MOTOR_ENCODER_DEGREES); // We have a motor stack. This is a stacked motor and it needs to be reversed compared to the other motors

Motor_Group leftMotorGroup ({leftMotor1, leftMotor2, leftMotor3});
Motor_Group rightMotorGroup ({rightMotor1, rightMotor2, rightMotor3});

void leftDrive(int32_t speed){
    cout << "left moving at " << speed << endl;
    leftMotorGroup.move(speed);
}

void rightDrive(int32_t speed){
    cout << "right moving at " << speed << endl;
    rightMotorGroup.move(speed);
}

int32_t accelerate(int32_t newSpeed, int32_t oldSpeed) {
    if(newSpeed == oldSpeed){
        cout << "at speed" << endl;
        return newSpeed;
    } else if(oldSpeed < newSpeed){
        cout << "move up to new speed" << endl;
        return oldSpeed + (int32_t)5;
    } else if(oldSpeed > newSpeed){
        cout << "move down to new speed" << endl;
        return oldSpeed - (int32_t)5;
    }
}