#include "main.h"

		pros::Controller master (CONTROLLER_MASTER);

	pros::Motor left1 (17, MOTOR_GEARSET_18, false);
	pros::Motor left2 (11, MOTOR_GEARSET_18, false); 
	pros::Motor right1 (1, MOTOR_GEARSET_18, true); 
	pros::Motor right2 (10, MOTOR_GEARSET_18, true); 

	pros::Motor wingLeft (7, MOTOR_GEARSET_36, false);
	pros::Motor wingRight (1, MOTOR_GEARSET_36, true);

double averageMotorPosition = (left1.get_position() + left2.get_position()+ right1.get_position() + right2.get_position())/4;

void drive (double distance, double speed ) { 

		double efficiency_modifier =2.5;

		double degreesTurned = (distance*efficiency_modifier/(double(3.1415)*int(10)))*360;

		left1.move_relative(degreesTurned, speed);
		left2.move_relative(degreesTurned, speed);

		right1.move_relative(degreesTurned, speed);
		right2.move_relative(degreesTurned, speed);	

	while (!((averageMotorPosition < degreesTurned+5) && (averageMotorPosition > degreesTurned-5))) {
    	// Continue running this loop as long as the motor is not within +-5 units of its goal
    	pros::delay(2);
		averageMotorPosition = (left1.get_position() + left2.get_position()+ right1.get_position() + right2.get_position())/4;
	}
}
void turn (double robot_degrees, double speed) {

double motor_degrees = robot_degrees;

	left1.move_relative(motor_degrees, speed);
	left2.move_relative(motor_degrees, speed);

	right1.move_relative(-motor_degrees, speed);
	right2.move_relative(-motor_degrees, speed);

	while (!((averageMotorPosition < motor_degrees+5) && (averageMotorPosition > motor_degrees-5))) {
    	// Continue running this loop as long as the motor is not within +-5 units of its goal
    	pros::delay(2);
		averageMotorPosition = (abs(left1.get_position()) + abs(left2.get_position())+ abs(right1.get_position()) + abs(right2.get_position()))/4;

	}
}
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
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
 */
void autonomous() {

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
	drive(80, 3600 );

	turn(180, 3600 );

}

void opcontrol() {


void opcontrol();


	int wingState = 1;

	
//	Ah, yes, the simple comment, definition of piston, controller , and motors

		pros::lcd::initialize();

	while (true) {
		

		int left1Control = (master.get_analog(ANALOG_LEFT_Y))-(0.5*master.get_analog(ANALOG_LEFT_X));
		int left2Control = (master.get_analog(ANALOG_LEFT_Y))-(0.5*master.get_analog(ANALOG_LEFT_X));

		int right1Control = (master.get_analog(ANALOG_LEFT_Y))+(0.5*master.get_analog(ANALOG_LEFT_X));
		int right2Control = (master.get_analog(ANALOG_LEFT_Y))+(0.5*master.get_analog(ANALOG_LEFT_X));


		left1.move(left1Control);
		left2.move(left2Control);

		right1.move(right1Control);
		right2.move(right2Control);

		pros::delay(2);


		switch(master.get_digital(DIGITAL_A)) {

			
			case true:

			wingRight.move_relative(90*wingState, 200);
			wingLeft.move_relative(90*wingState, 200);
			wingState *= -1;
			pros::delay(200);

			break;
		}
	}
}