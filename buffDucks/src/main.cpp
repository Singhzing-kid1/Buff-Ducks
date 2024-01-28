#include "main.h"

using namespace std;
using namespace pros;
using namespace duckTrace;
using namespace duckTraceHelper;


void llscreen() {
    // loop forever
    while (true) {
        lemlib::Pose pose = wheelThingyWithTracking.getPose(); // get the current position of the robot
        lcd::print(0, "x: %f", pose.x); // print the x position
        lcd::print(1, "y: %f", pose.y); // print the y position
        lcd::print(2, "heading: %f", pose.theta); // print the heading
        pros::delay(10);
    }
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	lcd::initialize();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task
 *
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended forpros::l
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *pros::l
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.pros::l
 */
void competition_initialize() {}

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
 *
 */
void autonomous() {
	
}

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
void opcontrol() {

	int32_t leftSpeed = 0;
	int32_t rightSpeed = 0;
	int32_t avgSpeed = 0;

	//fstream operatorLogFile = createLogFile(uniqueLogName(&ruleFile , controlMode::OPERATOR));

	//uint32_t startTime = millis();

	while (true) {
		rightSpeed = accelerate(deadzone(ANALOG_RIGHT_X, ANALOG_RIGHT_Y), rightSpeed);
		leftSpeed = accelerate(deadzone(ANALOG_LEFT_X, ANALOG_LEFT_Y), leftSpeed);

		if(master.get_analog(ANALOG_RIGHT_Y) != 0 || master.get_analog(ANALOG_LEFT_Y) != 0){
			switch(closeEnough(leftSpeed, rightSpeed)){
				case true:
					avgSpeed = (leftSpeed + rightSpeed)/2;
					leftMotorGroup = avgSpeed;
					rightMotorGroup = avgSpeed;
					break;

				case false:
					leftMotorGroup = leftSpeed;
					rightMotorGroup = rightSpeed;
					break;
			}
		} else {
			leftMotorGroup.brake();
			rightMotorGroup.brake();
		}

		//if(master.get_digital(DIGITAL_Y) != 0){ // current solution to get the log to save
		//	closeAndUpdateRuleFile(&ruleFile); // used to call break; but this allows us to keep driving after saving the log.
		//	operatorLogFile.close();
		//}

		//ostringstream payload = formulateDataString({leftMotorGroup[0], leftMotorGroup[1], leftMotorGroup[2]}, {rightMotorGroup[0], rightMotorGroup[1], rightMotorGroup[2]}, master, millis() - startTime);
		//writeLine(&operatorLogFile, &payload);

		pros::delay(20);
	}
}
