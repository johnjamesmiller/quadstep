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
void quadstep::motor_go(step_modes_t step_size, int number_of_steps, int torque)
{
	_torque = torque;
	
	// sets direction of rotation
	int dir = (number_of_steps > 0) ? HIGH : LOW;
	number_of_steps = abs(number_of_steps);

	set_speed(step_size);

	digitalWrite(_motor_dir, dir);

	// check to see what setp size was selected
	if(step_size == FULL)
	{
		digitalWrite(_motor_ms1, LOW);
		digitalWrite(_motor_ms2, LOW);
		digitalWrite(_motor_ms3, LOW);
	}
	else if(step_size == HALF)
	{
		digitalWrite(_motor_ms1, HIGH);
		digitalWrite(_motor_ms2, LOW);
		digitalWrite(_motor_ms3, LOW);
	}
	else if(step_size == QUARTER)
	{
		digitalWrite(_motor_ms1, LOW);
		digitalWrite(_motor_ms2, HIGH);
		digitalWrite(_motor_ms3, LOW);
	}
	else if(step_size == EIGHTH)
	{
		digitalWrite(_motor_ms1, HIGH);
		digitalWrite(_motor_ms2, HIGH);
		digitalWrite(_motor_ms3, LOW);
	}
	else if(step_size == SIXTEENTH)
	{
		digitalWrite(_motor_ms1, HIGH);
		digitalWrite(_motor_ms2, HIGH);
		digitalWrite(_motor_ms3, HIGH);
	}
	else Serial.println("error: incorrect value for step_size"); //print error code

	digitalWrite(_motor_enable, LOW);
	for(int i=1;i<=number_of_steps;i++)
	{
		//low to high transition moves one step
		digitalWrite(_motor_step, HIGH);
		delayMicroseconds(step); //low time
		digitalWrite(_motor_step, LOW);
		delayMicroseconds(step); // high time
	}
	digitalWrite(_motor_step, LOW);
	digitalWrite(_motor_enable, HIGH);
}

void quadstep::stall()
{
	digitalWrite(_motor_enable, LOW);
}

void quadstep::set_speed(step_modes_t step_size)
{
		step = STEPMIN + (_torque * 260) / step_size;
}
