/*

	created by Aaron Weiss, SparkFun electronics 2011
	
	Beerware - do what you wish with this ish

*/

#include "WProgram.h"
#include "quadstep.h"

#define STEPMIN	800

quadstep::quadstep()
{	
	//make sure the step lines are low on startup
	digitalWrite(_motor_step, LOW);
	Serial.begin(9600);
}

/////////////////////////////////////////////////////////
///////   Pin connections ///////////////////////////////
/////////////////////////////////////////////////////////
void quadstep::motor_pins(int motor_enable,int motor_dir,int motor_ms1,int motor_ms2,int motor_ms3, int motor_step)
{	
	pinMode(motor_enable, OUTPUT);
	pinMode(motor_dir, OUTPUT);
	pinMode(motor_step, OUTPUT);
	pinMode(motor_ms1, OUTPUT);
	pinMode(motor_ms2, OUTPUT);
	pinMode(motor_ms3, OUTPUT);

	digitalWrite(motor_enable, HIGH);
	digitalWrite(motor_dir, LOW);

	_motor_enable = motor_enable;
	_motor_dir = motor_dir;
	_motor_step = motor_step;
	_motor_ms1 = motor_ms1;
	_motor_ms2 = motor_ms2;
	_motor_ms3 = motor_ms3;
}

/////////////////////////////////////////////////////////
///////   Motor settings  ///////////////////////////////
/////////////////////////////////////////////////////////
void quadstep::go(step_modes_t step_size, int number_of_steps, int torque)
{
	_torque = torque;
	set_direction(number_of_steps);
	set_speed(step_size);
	set_microstep_format(step_size);
	enable();
	for(int i=1;i<=abs(number_of_steps);i++)
	{
		step();
	}
	disable();
}

void quadstep::stall()
{
	enable();
}

void quadstep::set_direction(int number_of_steps) {
	bool dir = (number_of_steps > 0) ? HIGH : LOW;
	digitalWrite(_motor_dir, dir);
}

void quadstep::set_speed(step_modes_t step_size)
{
		pulse_width = STEPMIN + (_torque * 260) / step_size;
}

void quadstep::set_microstep_format(step_modes_t step_size) {
	if (step_size == FULL) {
		digitalWrite(_motor_ms1, LOW);
		digitalWrite(_motor_ms2, LOW);
		digitalWrite(_motor_ms3, LOW);
	} else if (step_size == HALF) {
		digitalWrite(_motor_ms1, HIGH);
		digitalWrite(_motor_ms2, LOW);
		digitalWrite(_motor_ms3, LOW);
	} else if (step_size == QUARTER) {
		digitalWrite(_motor_ms1, LOW);
		digitalWrite(_motor_ms2, HIGH);
		digitalWrite(_motor_ms3, LOW);
	} else if (step_size == EIGHTH) {
		digitalWrite(_motor_ms1, HIGH);
		digitalWrite(_motor_ms2, HIGH);
		digitalWrite(_motor_ms3, LOW);
	} else if (step_size == SIXTEENTH) {
		digitalWrite(_motor_ms1, HIGH);
		digitalWrite(_motor_ms2, HIGH);
		digitalWrite(_motor_ms3, HIGH);
	} else{
		Serial.println("error: incorrect value for step_size");
	}
}

void quadstep::enable() {
	digitalWrite(_motor_enable, LOW);
}

void quadstep::step() {
	digitalWrite(_motor_step, HIGH);
	delayMicroseconds (pulse_width); //low time
	digitalWrite(_motor_step, LOW);
	delayMicroseconds(pulse_width); // high time
}

void quadstep::disable() {
	digitalWrite(_motor_enable, HIGH);
}
