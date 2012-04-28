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
	digitalWrite(_step_pin, LOW);
	Serial.begin(9600);
}

/////////////////////////////////////////////////////////
///////   Pin connections ///////////////////////////////
/////////////////////////////////////////////////////////
void quadstep::set_enable_pin(int enable_pin) {
	pinMode(enable_pin, OUTPUT);
	digitalWrite(enable_pin, HIGH);
	_enable_pin = enable_pin;
}

void quadstep::set_direction_pin(int direction_pin) {
	pinMode(direction_pin, OUTPUT);
	digitalWrite(direction_pin, LOW);
	_direction_pin = direction_pin;
}

void quadstep::set_step_pin(int step_pin) {
	pinMode(step_pin, OUTPUT);
	_step_pin = step_pin;
}

void quadstep::set_microstep_select_pins(int ms1_pin,int ms2_pin,int ms3_pin)
{
	pinMode(ms1_pin, OUTPUT);
	pinMode(ms2_pin, OUTPUT);
	pinMode(ms3_pin, OUTPUT);
	_ms1_pin = ms1_pin;
	_ms2_pin = ms2_pin;
	_ms3_pin = ms3_pin;
}

/////////////////////////////////////////////////////////
///////   Motor settings  ///////////////////////////////
/////////////////////////////////////////////////////////
void quadstep::go(step_modes_t step_size, int number_of_steps, int torque)
{
	set_direction(number_of_steps);
	set_speed(step_size, torque);
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
	digitalWrite(_direction_pin, dir);
}

void quadstep::set_speed(step_modes_t step_size, int torque)
{
		pulse_width = STEPMIN + (torque * 260) / step_size;
}

void quadstep::set_microstep_format(step_modes_t step_size) {
	if (step_size == FULL) {
		digitalWrite(_ms1_pin, LOW);
		digitalWrite(_ms2_pin, LOW);
		digitalWrite(_ms3_pin, LOW);
	} else if (step_size == HALF) {
		digitalWrite(_ms1_pin, HIGH);
		digitalWrite(_ms2_pin, LOW);
		digitalWrite(_ms3_pin, LOW);
	} else if (step_size == QUARTER) {
		digitalWrite(_ms1_pin, LOW);
		digitalWrite(_ms2_pin, HIGH);
		digitalWrite(_ms3_pin, LOW);
	} else if (step_size == EIGHTH) {
		digitalWrite(_ms1_pin, HIGH);
		digitalWrite(_ms2_pin, HIGH);
		digitalWrite(_ms3_pin, LOW);
	} else if (step_size == SIXTEENTH) {
		digitalWrite(_ms1_pin, HIGH);
		digitalWrite(_ms2_pin, HIGH);
		digitalWrite(_ms3_pin, HIGH);
	} else{
		Serial.println("error: incorrect value for step_size");
	}
}

void quadstep::enable() {
	digitalWrite(_enable_pin, LOW);
}

void quadstep::step() {
	digitalWrite(_step_pin, HIGH);
	delayMicroseconds (pulse_width); //low time
	digitalWrite(_step_pin, LOW);
	delayMicroseconds(pulse_width); // high time
}

void quadstep::disable() {
	digitalWrite(_enable_pin, HIGH);
}
