#include "main.h"

using namespace std;
using namespace pros;

Controller master (E_CONTROLLER_MASTER);

int32_t deadzone(controller_analog_e_t valueY, controller_analog_e_t valueX){
    if ((master.get_analog(valueY) >= 27 || master.get_analog(valueY) <= -27) && master.get_analog(valueX) == 0){
        return master.get_analog(valueY);
    } else if ((master.get_analog(valueY) >= 27 || master.get_analog(valueY) <= -27) && master.get_analog(valueX) != 0){
       if(master.get_analog(valueY) < 0){
        return (int32_t)-hypot((double)master.get_analog(valueX), (double)master.get_analog(valueY));
       } else if(master.get_analog(valueY) > 0){
        return (int32_t)hypot((double)master.get_analog(valueX), (double)master.get_analog(valueY));
       }
    } else {
        return (int32_t)0;
    }
}