#include "main.h"

using namespace std;
using namespace pros;

driverSettings mainSettings;
driverSettings leo;
driverSettings driver2;

driverSettings initDriver(driverSettings driver, int member){
    switch(member){
        case 0: // each driver will be given a single digit unique integer. their driver settings will be set here:
            driver.deadZoneLimit = 27;
            driver.clampLimit = 100;
            driver.acclerationInterval = (int32_t)3;
            return driver;

        case 1:
            driver.deadZoneLimit = 27;
            driver.clampLimit = 100;
            driver.acclerationInterval = (int32_t)3;
            return driver;


    }

}

int driverIndex = 0; // default to main settings
bool nonDefaultDriver;

vector<driverSettings> drivers = {mainSettings, initDriver(leo, 0), initDriver(driver2, 1)};






