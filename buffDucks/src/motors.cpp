#include "main.h"

using namespace std;
using namespace pros;

Motor leftMotor1 (1, E_MOTOR_GEAR_GREEN, false, E_MOTOR_ENCODER_DEGREES);
Motor leftMotor2 (2, E_MOTOR_GEAR_GREEN, false, E_MOTOR_ENCODER_DEGREES);
Motor leftMotor3 (3, E_MOTOR_GEAR_GREEN, true, E_MOTOR_ENCODER_DEGREES); // We have a motor stack. This is a stacked motor and it needs to be reversed

Motor rightMotor1 (1, E_MOTOR_GEAR_GREEN, false, E_MOTOR_ENCODER_DEGREES);
Motor rightMotor2 (2, E_MOTOR_GEAR_GREEN, false, E_MOTOR_ENCODER_DEGREES);
Motor rightMotor3 (3, E_MOTOR_GEAR_GREEN, true, E_MOTOR_ENCODER_DEGREES); // We have a motor stack. This is a stacked motor and it needs to be reversed

Motor_Group leftMotorGroup ({leftMotor1, leftMotor2, leftMotor3});
Motor_Group rightMotorGroup ({rightMotor1, rightMotor2, rightMotor3});



void leftDrive(int32_t speed){
    leftMotorGroup.move(speed);
}

void rightDrive(int32_t speed){
    rightMotorGroup.move(speed);
}