#include "main.h"

using namespace std;
using namespace pros;
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void onLeftButton(){
	nonDefaultDriver = true;
	driverIndex = 1;
}

void onCenterButton(){
	nonDefaultDriver = true;
	driverIndex = 2;
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize(){
	lcd::initialize();
	lcd::set_background_color(0, 0, 0);
	lcd::set_text_color(255, 255, 255);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled(){}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize(){}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous(){}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol(){

	int32_t leftSpeed = 0;                    // 
	int32_t rightSpeed = 0;                   //  
	int32_t avgSpeed = 0;                     //
                                              //
	int count = 0;                            //   
                                              //
	bool leftMotor1TempWarning = false;       // define some opControl variables.
	bool leftMotor2TempWarning = false;       //
	bool leftMotor3TempWarning = false;       //
                                              //
	bool rightMotor1TempWarning = false;      //
	bool rightMotor2TempWarning = false;      //
	bool rightMotor3TempWarning = false;      //

	while (true){

		lcd::register_btn0_cb(onLeftButton);    // toggles to change driver profile after code has started. FOR TESTING PURPOSES ONLY.
		lcd::register_btn0_cb(onCenterButton);  // 

		leftSpeed = accelerate(deadzone(ANALOG_LEFT_Y, ANALOG_LEFT_X), leftSpeed);       // get analog stick inputs and run them through functions to get left/right speed values.
		rightSpeed = accelerate(deadzone(ANALOG_RIGHT_Y, ANALOG_RIGHT_X), rightSpeed);   //

		if(master.get_analog(ANALOG_LEFT_Y) != 0 || master.get_analog(ANALOG_RIGHT_Y) != 0){ // check if any of the analog sticks are moving in the y axis.
			switch(closeEnough(leftSpeed, rightSpeed)){ // check if the leftSpeed and rightSpeed are within 5 of each other.
				case true: // if true then
					avgSpeed = (leftSpeed + rightSpeed)/2; // avg left and right speeds together.
					leftDrive(avgSpeed);  // apply the avgSpeed to both the left motor group and right motor group.
					rightDrive(avgSpeed); //
					break;

				case false: // if false then
					leftDrive(leftSpeed);   // set the leftSpeed to the left motor group and the rightSpeed to the right motor gorup.
					rightDrive(rightSpeed); //
					break;
			}
		} else { // if none of the sticks are moving then
			leftMotorGroup.move(0);   // set the input voltages to zero because for some reason setting the motor brake mode to coast does not work. this is the same as setting the 
			rightMotorGroup.move(0);  // brake mode to coast.
		}


		if(master.get_digital(DIGITAL_R1) == 1){                   // triball intake stuff. self explanitory.
			intakeMotor.move(drivers[driverIndex].intakeSpeed);    
		} else{
			intakeMotor.brake();
		}

		switch(driverIndex){ // communicates the active driver profile 
			case 0:
				lcd::print(0, "Default Driver Settings");
				break;
			case 1:
				lcd::print(0, "Leo's Settings");
				break;
			case 2:
				lcd::print(0, "Backup Driver's Settings");
				break;
		}

		// shows the current motor temps so we can tell if they are overheating
		lcd::print(1, "Left Motors: | Right Motors: ");
		lcd::print(2, "1 (port 1): %g | 1 (port 4): %g", leftMotor1.get_temperature(), rightMotor1.get_temperature());
		lcd::print(3, "2 (port 10):%g | 2 (port 5): %g", leftMotor2.get_temperature(), rightMotor2.get_temperature());
		lcd::print(4, "3 (port 3): %g | 3 (port 6): %g", leftMotor3.get_temperature(), rightMotor3.get_temperature());

		if(!(count%25)){ // rumbles the comtrollers in a specific pattern to communicate which motor is overheating during competition.
			leftMotor1TempWarning = tempWarningRumbler("left", 1, leftMotor1, leftMotor1TempWarning);
			leftMotor2TempWarning = tempWarningRumbler("left", 2, leftMotor2, leftMotor2TempWarning);
			leftMotor3TempWarning = tempWarningRumbler("left", 3, leftMotor3, leftMotor3TempWarning);

			rightMotor1TempWarning = tempWarningRumbler("right", 1, rightMotor1, rightMotor1TempWarning);
			rightMotor2TempWarning = tempWarningRumbler("right", 2, rightMotor2, rightMotor2TempWarning);
			rightMotor3TempWarning = tempWarningRumbler("right", 3, rightMotor3, rightMotor3TempWarning);
		}
		count++;

		delay(2);
		
		/*
		The missile knows where it is at all times. It knows this because it knows where it isn't. 
		By subtracting where it is from where it isn't, or where it isn't from where it is (whichever is greater), it obtains a difference, or deviation. 
		The guidance subsystem uses deviations to generate corrective commands to drive the missile from a position where it is to a position where it isn't, and arriving at a position where it wasn't, it now is. 
		Consequently, the position where it is, is now the position that it wasn't, and it follows that the position that it was, is now the position that it isn't.
		In the event that the position that it is in is not the position that it wasn't, the system has acquired a variation, the variation being the difference between where the missile is, and where it wasn't. 
		If variation is considered to be a significant factor, it too may be corrected by the GEA. However, the missile must also know where it was.
		The missile guidance computer scenario works as follows. 
		Because a variation has modified some of the information the missile has obtained, it is not sure just where it is. 
		However, it is sure where it isn't, within reason, and it knows where it was. 
		It now subtracts where it should be from where it wasn't, or vice-versa, and by differentiating this from the algebraic sum of where it shouldn't be, and where it was, it is able to obtain the deviation and its variation, which is called error.
		*/
	}
}
