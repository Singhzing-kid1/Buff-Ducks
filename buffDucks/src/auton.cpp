#include "main.h"

using namespace std;
using namespace pros;

double error(double target, double current){
    return target - current;
}

double integrate(double error, double time){
    return error * time;
}

double derivate(double error, double lastError, double time){
    return (error - lastError)/time;
}

double pid(double error, double integration, double derivation, double proportionalGain, double integralGain, double derivativeGain){
    return (proportionalGain * error) + (integralGain * integration) + (derivativeGain * derivation); 
}

double currentDistance(Motor motor){
    return ((abs(motor.get_position())/360)*(6/10)) * 2 * pi * 0.041275;
}

double getArcDistance(double theta){
    return (2*pi*0.125)*((theta)/360);
}

void pidMove(double target, int speed){
    bool isAtTarget = false;

    int count = 0;

    double current;
    double err;
    double lastErr;

    double integral;
    double derivative;
    double output;

    const double kP = 0.1;
    const double kI = 0.01;
    const double kD = 0.05;

    rightMotor3.set_encoder_units(E_MOTOR_ENCODER_DEGREES);
    rightMotor3.tare_position();

    while(!isAtTarget){
        current = currentDistance(rightMotor3);
        
        cout << "current: " << current << endl;
        cout << "at target? " << isAtTarget << endl; // make this so that it uses the motor encoder values.

        err = error(target, current);
        integral += integrate(err, (double)count);
        derivative = derivate(err, lastErr, (double)count);

        output = pid(err, integral, derivative, kP, kI, kD);

        leftMotorGroup.move(output * speed);
        rightMotorGroup.move(output * speed);

        if (current == target){
            isAtTarget = true;
            break;
        }

        lastErr = err;
        count++;
        delay(2);
    }

    leftMotorGroup.brake();
    rightMotorGroup.brake();
}


void pidTurnRight(double target, int speed){

    bool isAtTarget = false;

    int count = 0;

    double current;
    double err;
    double lastErr;

    double integral;
    double derivative;
    double output;

    const double kP = 0.1;
    const double kI = 0.01;
    const double kD = 0.05;

    rightMotor3.set_encoder_units(E_MOTOR_ENCODER_DEGREES);
    rightMotor3.tare_position();

    while(!isAtTarget){
        current = currentDistance(rightMotor3);

        err = error(target, current);
        integral += integrate(err, (double)count);
        derivative = derivate(err, lastErr, double(count));

        output = pid(err, integral, derivative, kP, kI, kD);

        leftMotorGroup.move(output * speed);
        rightMotorGroup.move(output * -speed);

        if (current == target){
            isAtTarget = true;
            break;
        }

        lastErr = err;
        count++;
        delay(2);
    }
}

void pidTurnLeft(double target, int speed){
    bool isAtTarget = false;

    int count = 0;

    double current;
    double err;
    double lastErr;

    double integral;
    double derivative;
    double output;

    const double kP = 0.1;
    const double kI = 0.01;
    const double kD = 0.05;

    rightMotor3.set_encoder_units(E_MOTOR_ENCODER_DEGREES);
    rightMotor3.tare_position();

    while(!isAtTarget){
        current = currentDistance(leftMotor3);

        err = error(target, current);
        integral += integrate(err, (double)count);
        derivative = derivate(err, lastErr, double(count));

        output = pid(err, integral, derivative, kP, kI, kD);

        leftMotorGroup.move(output * -speed);
        rightMotorGroup.move(output * speed);

        if (current == target){
            isAtTarget = true;
            break;
        }

        lastErr = err;
        count++;
        delay(2);
    }
}