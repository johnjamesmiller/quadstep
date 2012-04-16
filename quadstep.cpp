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
	digitalWrite(_motor_step_1, LOW);
	digitalWrite(_motor_step_2, LOW);
	digitalWrite(_motor_step_3, LOW);
	digitalWrite(_motor_step_4, LOW);
	
	Serial.begin(9600);
}

/////////////////////////////////////////////////////////
///////   Pin connections ///////////////////////////////
/////////////////////////////////////////////////////////
void quadstep::motor_pins(int motnum,int motor_enable,int motor_dir,int motor_ms1,int motor_ms2,int motor_ms3, int motor_step)
{	
	pinMode(motor_enable, OUTPUT);
	pinMode(motor_dir, OUTPUT);
	pinMode(motor_step, OUTPUT);
	pinMode(motor_ms1, OUTPUT);
	pinMode(motor_ms2, OUTPUT);
	pinMode(motor_ms3, OUTPUT);

	digitalWrite(motor_enable, HIGH);
	digitalWrite(motor_dir, LOW);

	if(motnum == 1)
	{
		_motor_enable_1 = motor_enable;
		_motor_dir_1 = motor_dir;
		_motor_step_1 = motor_step;
		_motor_ms_11 = motor_ms1;
		_motor_ms_12 = motor_ms2;
		_motor_ms_13 = motor_ms3;
	}
	else if(motnum == 2)
	{
		_motor_enable_2 = motor_enable;
		_motor_dir_2 = motor_dir;
		_motor_step_2 = motor_step;
		_motor_ms_21 = motor_ms1;
		_motor_ms_22 = motor_ms2;
		_motor_ms_23 = motor_ms3;
	}
	else if(motnum == 3)
	{
		_motor_enable_3 = motor_enable;
		_motor_dir_3 = motor_dir;
		_motor_step_3 = motor_step;
		_motor_ms_31 = motor_ms1;
		_motor_ms_32 = motor_ms2;
		_motor_ms_33 = motor_ms3;
	}
	else if(motnum == 4)
	{
		_motor_enable_4 = motor_enable;
		_motor_dir_4 = motor_dir;
		_motor_step_4 = motor_step;
		_motor_ms_41 = motor_ms1;
		_motor_ms_42 = motor_ms2;
		_motor_ms_43 = motor_ms3;
	}
	else Serial.println("error: incorrect value for motor_pins, motor number"); //print error code
}

/////////////////////////////////////////////////////////
///////   Motor settings  ///////////////////////////////
/////////////////////////////////////////////////////////
void quadstep::motor_go(int motnum, step_modes_t step_size, int number_of_steps, int torque)
{
	_torque = torque;
	
	// sets direction of rotation
	int dir = (number_of_steps > 0) ? HIGH : LOW;
	number_of_steps = abs(number_of_steps);

	//sets speed
	current_control(step_size);

	if(motnum == 1)
	{	
		digitalWrite(_motor_dir_1, dir);

		// check to see what setp size was selected
		if(step_size == FULL)
		{
			//sets step_size
			digitalWrite(_motor_ms_11, LOW);    
			digitalWrite(_motor_ms_12, LOW);    
			digitalWrite(_motor_ms_13, LOW);
		}
		else if(step_size == HALF)
		{
			digitalWrite(_motor_ms_11, HIGH);    
			digitalWrite(_motor_ms_12, LOW);    
			digitalWrite(_motor_ms_13, LOW);
		}
		else if(step_size == QUARTER)
		{
			digitalWrite(_motor_ms_11, LOW);    
			digitalWrite(_motor_ms_12, HIGH);    
			digitalWrite(_motor_ms_13, LOW);
		}
		else if(step_size == EIGHTH)
		{
			digitalWrite(_motor_ms_11, HIGH);    
			digitalWrite(_motor_ms_12, HIGH);    
			digitalWrite(_motor_ms_13, LOW);
		}
		else if(step_size == SIXTEENTH)
		{
			digitalWrite(_motor_ms_11, HIGH);    
			digitalWrite(_motor_ms_12, HIGH);    
			digitalWrite(_motor_ms_13, HIGH);
		}
		else Serial.println("error: incorrect value for step_size"); //print error code

		digitalWrite(_motor_enable_1, LOW);
		for(int i=1;i<=number_of_steps;i++)
		{
			//low to high transition moves one step
			digitalWrite(_motor_step_1, HIGH);
			delayMicroseconds(step);
			digitalWrite(_motor_step_1, LOW);
			delayMicroseconds(step);
		}
		digitalWrite(_motor_step_1, LOW);
		digitalWrite(_motor_enable_1, HIGH);
	}
	
	if(motnum == 2)
	{
		digitalWrite(_motor_dir_2, dir);
		
		// check to see what setp size was selected
		if(step_size == FULL)
		{
			digitalWrite(_motor_ms_21, LOW);    
			digitalWrite(_motor_ms_22, LOW);    
			digitalWrite(_motor_ms_23, LOW);
		}
		else if(step_size == HALF)
		{
			digitalWrite(_motor_ms_21, HIGH);    
			digitalWrite(_motor_ms_22, LOW);    
			digitalWrite(_motor_ms_23, LOW);
		}
		else if(step_size == QUARTER)
		{
			digitalWrite(_motor_ms_21, LOW);    
			digitalWrite(_motor_ms_22, HIGH);    
			digitalWrite(_motor_ms_23, LOW);
		}
		else if(step_size == EIGHTH)
		{
			digitalWrite(_motor_ms_21, HIGH);    
			digitalWrite(_motor_ms_22, HIGH);    
			digitalWrite(_motor_ms_23, LOW);
		}
		else if(step_size == SIXTEENTH)
		{
			digitalWrite(_motor_ms_21, HIGH);    
			digitalWrite(_motor_ms_22, HIGH);    
			digitalWrite(_motor_ms_23, HIGH);
		}
		else Serial.println("error: incorrect value for step_size"); //print error code

		digitalWrite(_motor_enable_2, LOW);
		for(int i=1;i<=number_of_steps;i++)
		{
			//low to high transition moves one step
			digitalWrite(_motor_step_2, HIGH);
			delayMicroseconds(step); //low time
			digitalWrite(_motor_step_2, LOW);
			delayMicroseconds(step); // high time
		}
		digitalWrite(_motor_step_2, LOW);
		digitalWrite(_motor_enable_2, HIGH);
	}
	
	if(motnum == 3)
	{
		digitalWrite(_motor_dir_3, dir);
		
		// check to see what setp size was selected
		if(step_size == FULL)
		{
			digitalWrite(_motor_ms_31, LOW);    
			digitalWrite(_motor_ms_32, LOW);    
			digitalWrite(_motor_ms_33, LOW);
		}
		else if(step_size == HALF)
		{
			digitalWrite(_motor_ms_31, HIGH);    
			digitalWrite(_motor_ms_32, LOW);    
			digitalWrite(_motor_ms_33, LOW);
		}
		else if(step_size == QUARTER)
		{
			digitalWrite(_motor_ms_31, LOW);    
			digitalWrite(_motor_ms_32, HIGH);    
			digitalWrite(_motor_ms_33, LOW);
		}
		else if(step_size == EIGHTH)
		{
			digitalWrite(_motor_ms_31, HIGH);    
			digitalWrite(_motor_ms_32, HIGH);    
			digitalWrite(_motor_ms_33, LOW);
		}
		else if(step_size == SIXTEENTH)
		{
			digitalWrite(_motor_ms_31, HIGH);    
			digitalWrite(_motor_ms_32, HIGH);    
			digitalWrite(_motor_ms_33, HIGH);
		}
		else Serial.println("error: incorrect value for step_size"); //print error code

		digitalWrite(_motor_enable_3, LOW);    // enable motor 1
		for(int i=1;i<=number_of_steps;i++)
		{
			//low to high transition moves one step
			digitalWrite(_motor_step_3, HIGH);
			delayMicroseconds(step); //high time
			digitalWrite(_motor_step_3, LOW);
			delayMicroseconds(step); //low time
		}
		digitalWrite(_motor_step_3, LOW);
		digitalWrite(_motor_enable_3, HIGH);    // disable motor 1
	}
	
	if(motnum == 4)
	{
		digitalWrite(_motor_dir_4, dir);

		// check to see what setp size was selected
		if(step_size == FULL)
		{
			digitalWrite(_motor_ms_41, LOW);    
			digitalWrite(_motor_ms_42, LOW);    
			digitalWrite(_motor_ms_43, LOW);
		}

		else if(step_size == HALF)
		{
			digitalWrite(_motor_ms_41, HIGH);    
			digitalWrite(_motor_ms_42, LOW);    
			digitalWrite(_motor_ms_43, LOW);
		}

		else if(step_size == QUARTER)
		{
			digitalWrite(_motor_ms_41, LOW);    
			digitalWrite(_motor_ms_42, HIGH);    
			digitalWrite(_motor_ms_43, LOW);
		}
		else if(step_size == EIGHTH)
		{
			digitalWrite(_motor_ms_41, HIGH);    
			digitalWrite(_motor_ms_42, HIGH);    
			digitalWrite(_motor_ms_43, LOW);
		}
		else if(step_size == SIXTEENTH)
		{
			digitalWrite(_motor_ms_41, HIGH);    
			digitalWrite(_motor_ms_42, HIGH);    
			digitalWrite(_motor_ms_43, HIGH);
		}
		else Serial.println("error: incorrect value for step_size"); //print error code

		digitalWrite(_motor_enable_4, LOW);
		for(int i=1;i<=number_of_steps;i++)
		{
			//low to high transition moves one step
			digitalWrite(_motor_step_4, HIGH);
			delayMicroseconds(step);
			digitalWrite(_motor_step_4, LOW);
			delayMicroseconds(step);
		}
		digitalWrite(_motor_step_4, LOW);
		digitalWrite(_motor_enable_4, HIGH);

	}
	else Serial.println("error: incorrect value for motor_go"); //print error code
}

void quadstep::stall(int motnum)
{
	if(motnum == 1)
	{
		digitalWrite(_motor_enable_1, LOW);
	}
	else if(motnum == 2)
	{
		digitalWrite(_motor_enable_2, LOW);
	}	
	else if(motnum == 3)
	{
		digitalWrite(_motor_enable_3, LOW);
	}	
	else if(motnum == 4)
	{
		digitalWrite(_motor_enable_4, LOW);
	}
	else Serial.println("error: incorrect value for stall"); //print error code		
}

void quadstep::current_control(step_modes_t step_size)
{
		step = STEPMIN + (_torque * 260) / step_size;
}
