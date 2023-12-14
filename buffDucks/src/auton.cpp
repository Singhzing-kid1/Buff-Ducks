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

double pidMove(double target, int speed){
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

    while(!isAtTarget){
        current = 10; // make this so that it uses the motor encoder values.

        err = error(target, current);
        integral = integrate(err, (double)count);
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
}
