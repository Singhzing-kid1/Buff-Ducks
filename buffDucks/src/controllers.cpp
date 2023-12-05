#include "main.h"

using namespace std;
using namespace pros;

Controller master (E_CONTROLLER_MASTER);

int32_t deadzone(controller_analog_e_t valueY, controller_analog_e_t valueX){
    if ((master.get_analog(valueY) >= drivers[driverIndex].deadZoneLimit || master.get_analog(valueY) <= -drivers[driverIndex].deadZoneLimit) && master.get_analog(valueX) == 0){ // some ugly computation to figure out whether or not the analog sticks are being moved past a horizontal line that determines the deadzones 
        return master.get_analog(valueY);
    } else if ((master.get_analog(valueY) >= drivers[driverIndex].deadZoneLimit || master.get_analog(valueY) <= -drivers[driverIndex].deadZoneLimit) && master.get_analog(valueX) != 0){
        if(master.get_analog(valueY) < 0){
            if(-hypot((double)master.get_analog(valueX), (double)master.get_analog(valueY)) <= -drivers[driverIndex].deadZoneLimit){
                return (int32_t)-hypot((double)master.get_analog(valueX), (double)master.get_analog(valueY));
            }
        } else if(master.get_analog(valueY) > 0){
            if(hypot((double)master.get_analog(valueX), (double)master.get_analog(valueY)) >= drivers[driverIndex].deadZoneLimit){
                return (int32_t)hypot((double)master.get_analog(valueX), (double)master.get_analog(valueY));
            }
        }
    } else{
        return (int32_t)0;
    }
}

int32_t clamp(int32_t analogValue){
    if(abs(analogValue) >= drivers[driverIndex].clampLimit){
        if(analogValue < 0){
            return (int32_t)-drivers[driverIndex].clampLimit;
        } else if(analogValue > 0){
            return (int32_t)drivers[driverIndex].clampLimit;
        }
    } else{
        return analogValue;
    }
}

bool tempWarningRumbler(string side, int motorNum, Motor motor, bool haveWarned){
    if(!haveWarned){
        if(motor.get_temperature() >= 50){
            if(side == "right"){
                switch(motorNum){
                    case 1:
                        master.rumble(". - .    . - -");
                        return true;
                        break;

                    case 2:
                        master.rumble(". - .    . . -");
                        return true;
                        break;

                    case 3:
                        master.rumble(". - .    . . .");
                        return true;
                        break;
                }

            } else if(side == "left"){
                switch(motorNum){
                    case 1:
                        master.rumble(". - . .    . - -");
                        return true;
                        break;

                    case 2:
                        master.rumble(". - . .    . . -");
                        return true;
                        break;

                    case 3:
                        master.rumble(". - . .    . . .");
                        return true;
                        break;
                }

            }
        } else{
            return false;
        }
    } else{
        return true;
    }


}

bool closeEnough(int32_t leftInput, int32_t rightInput){
    if (abs(leftInput - rightInput) <= 5){
        return true;
    } else {
        return false;
    }
}