/*

	created by Aaron Weiss, SparkFun electronics 2011
	
	Beerware - do what you wish with this ish

*/

#include "WProgram.h"
#include "quadstep.h"

#define STEPMIN	800

quadstep::quadstep()
{	
	pinMode(11, OUTPUT); //PB5
	pinMode(5, OUTPUT); //PE3
	pinMode(6, OUTPUT); //PH3
	pinMode(46, OUTPUT); //PL3
	
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
	if(motnum == 1)
	{
		pinMode(motor_enable, OUTPUT);
		pinMode(motor_dir, OUTPUT);
		pinMode(motor_step, OUTPUT);
		pinMode(motor_ms1, OUTPUT);
		pinMode(motor_ms2, OUTPUT);
		pinMode(motor_ms3, OUTPUT);
		
		digitalWrite(motor_enable, HIGH);
		digitalWrite(motor_dir, LOW);
		_motor_enable_1 = motor_enable;
		_motor_dir_1 = motor_dir;
		_motor_step_1 = motor_step;
		_motor_ms_11 = motor_ms1;
		_motor_ms_12 = motor_ms2;
		_motor_ms_13 = motor_ms3;
	}
	else if(motnum == 2)
	{
		pinMode(motor_enable, OUTPUT);
		pinMode(motor_dir, OUTPUT);
		pinMode(motor_step, OUTPUT);
		pinMode(motor_ms1, OUTPUT);
		pinMode(motor_ms2, OUTPUT);
		pinMode(motor_ms3, OUTPUT);
		
		digitalWrite(motor_enable, HIGH);
		digitalWrite(motor_dir, LOW);
		_motor_enable_2 = motor_enable;
		_motor_dir_2 = motor_dir;
		_motor_step_2 = motor_step;
		_motor_ms_21 = motor_ms1;
		_motor_ms_22 = motor_ms2;
		_motor_ms_23 = motor_ms3;
	}
	else if(motnum == 3)
	{
		pinMode(motor_enable, OUTPUT);
		pinMode(motor_dir, OUTPUT);
		pinMode(motor_step, OUTPUT);
		pinMode(motor_ms1, OUTPUT);
		pinMode(motor_ms2, OUTPUT);
		pinMode(motor_ms3, OUTPUT);
		
		digitalWrite(motor_enable, HIGH);
		digitalWrite(motor_dir, LOW);
		_motor_enable_3 = motor_enable;
		_motor_dir_3 = motor_dir;
		_motor_step_3 = motor_step;
		_motor_ms_31 = motor_ms1;
		_motor_ms_32 = motor_ms2;
		_motor_ms_33 = motor_ms3;
	}
	else if(motnum == 4)
	{
		pinMode(motor_enable, OUTPUT);
		pinMode(motor_dir, OUTPUT);
		pinMode(motor_step, OUTPUT);
		pinMode(motor_ms1, OUTPUT);
		pinMode(motor_ms2, OUTPUT);
		pinMode(motor_ms3, OUTPUT);
		
		digitalWrite(motor_enable, HIGH);
		digitalWrite(motor_dir, LOW);
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
void quadstep::motor_go(int motnum, int step_size, int number_of_steps, int torque)
{
	_torque = torque;
	
	if(motnum == 1)
	{	
		// sets direction of rotation
		int dir = (number_of_steps > 0) ? HIGH : LOW;
		number_of_steps = abs(number_of_steps);
		
		digitalWrite(_motor_dir_1, dir);
		
		// check to see what setp size was selected
		if(step_size == 1)
		{
			//sets speed
			current_control(1);
			
			//sets step_size
			digitalWrite(_motor_ms_11, LOW);    
			digitalWrite(_motor_ms_12, LOW);    
			digitalWrite(_motor_ms_13, LOW);
			
			digitalWrite(_motor_enable_1, LOW);    // enable motor 1
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				digitalWrite(_motor_step_1, HIGH);
				delayMicroseconds(step1); //high time
				digitalWrite(_motor_step_1, LOW);
				delayMicroseconds(step1); // low time
			}
			digitalWrite(_motor_step_1, LOW);
			digitalWrite(_motor_enable_1, HIGH);    // disable motor 1
		}
		
		else if(step_size == 2)
		{
			//sets speed
			current_control(2);
			
			digitalWrite(_motor_ms_11, HIGH);    
			digitalWrite(_motor_ms_12, LOW);    
			digitalWrite(_motor_ms_13, LOW);
			
			digitalWrite(_motor_enable_1, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				digitalWrite(_motor_step_1, HIGH);
				delayMicroseconds(step2); 
				digitalWrite(_motor_step_1, LOW);
				delayMicroseconds(step2);
			}
			digitalWrite(_motor_step_1, LOW);
			digitalWrite(_motor_enable_1, HIGH);    
		}
		
		else if(step_size == 4)
		{
			//sets speed
			current_control(4);
			
			digitalWrite(_motor_ms_11, LOW);    
			digitalWrite(_motor_ms_12, HIGH);    
			digitalWrite(_motor_ms_13, LOW);
			
			digitalWrite(_motor_enable_1, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				digitalWrite(_motor_step_1, HIGH);
				delayMicroseconds(step4);
				digitalWrite(_motor_step_1, LOW);
				delayMicroseconds(step4); 
			}
			digitalWrite(_motor_step_1, LOW);
			digitalWrite(_motor_enable_1, HIGH);    
		}
		else if(step_size == 8)
		{
			//sets speed
			current_control(8);
			
			digitalWrite(_motor_ms_11, HIGH);    
			digitalWrite(_motor_ms_12, HIGH);    
			digitalWrite(_motor_ms_13, LOW);
			
			digitalWrite(_motor_enable_1, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				digitalWrite(_motor_step_1, HIGH);
				delayMicroseconds(step8);
				digitalWrite(_motor_step_1, LOW);
				delayMicroseconds(step8); 
			}
			digitalWrite(_motor_step_1, LOW);
			digitalWrite(_motor_enable_1, HIGH);    
		}
		else if(step_size == 16)
		{
			//sets speed
			current_control(16);
			
			digitalWrite(_motor_ms_11, HIGH);    
			digitalWrite(_motor_ms_12, HIGH);    
			digitalWrite(_motor_ms_13, HIGH);
			
			digitalWrite(_motor_enable_1, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				digitalWrite(_motor_step_1, HIGH);
				delayMicroseconds(step16); 
				digitalWrite(_motor_step_1, LOW);
				delayMicroseconds(step16); 
			}
			digitalWrite(_motor_step_1, LOW);
			digitalWrite(_motor_enable_1, HIGH);   
		}
		else Serial.println("error: incorrect value for step_size"); //print error code
	}
	
	if(motnum == 2)
	{
		// sets direction of rotation
		int dir = (number_of_steps > 0) ? HIGH : LOW;
		number_of_steps = abs(number_of_steps);
		
		digitalWrite(_motor_dir_2, dir);
		
		// check to see what setp size was selected
		if(step_size == 1)
		{
			//sets speed
			current_control(1);
			
			digitalWrite(_motor_ms_21, LOW);    
			digitalWrite(_motor_ms_22, LOW);    
			digitalWrite(_motor_ms_23, LOW);
			
			digitalWrite(_motor_enable_2, LOW);    // enable motor 1
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				digitalWrite(_motor_step_2, HIGH);
				delayMicroseconds(step1); 
				digitalWrite(_motor_step_2, LOW);
				delayMicroseconds(step1); 
			}
			digitalWrite(_motor_step_2, LOW);
			digitalWrite(_motor_enable_2, HIGH);    // disable motor 1
		}
		
		else if(step_size == 2)
		{
			//sets speed
			current_control(2);
			
			digitalWrite(_motor_ms_21, HIGH);    
			digitalWrite(_motor_ms_22, LOW);    
			digitalWrite(_motor_ms_23, LOW);
			
			digitalWrite(_motor_enable_2, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				digitalWrite(_motor_step_2, HIGH);
				delayMicroseconds(step2); //low time
				digitalWrite(_motor_step_2, LOW);
				delayMicroseconds(step2); // high time
			}
			digitalWrite(_motor_step_2, LOW);
			digitalWrite(_motor_enable_2, HIGH);    
		}
		
		else if(step_size == 4)
		{
			//sets speed
			current_control(4);
			
			digitalWrite(_motor_ms_21, LOW);    
			digitalWrite(_motor_ms_22, HIGH);    
			digitalWrite(_motor_ms_23, LOW);
			
			digitalWrite(_motor_enable_2, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				digitalWrite(_motor_step_2, HIGH);
				delayMicroseconds(step4); //low time
				digitalWrite(_motor_step_2, LOW);
				delayMicroseconds(step4); // high time
			}
			digitalWrite(_motor_step_2, LOW);
			digitalWrite(_motor_enable_2, HIGH);    
		}
		else if(step_size == 8)
		{
			//sets speed
			current_control(8);
			
			digitalWrite(_motor_ms_21, HIGH);    
			digitalWrite(_motor_ms_22, HIGH);    
			digitalWrite(_motor_ms_23, LOW);
			
			digitalWrite(_motor_enable_2, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				digitalWrite(_motor_step_2, HIGH);
				delayMicroseconds(step8); //low time
				digitalWrite(_motor_step_2, LOW);
				delayMicroseconds(step8); // high time
			}
			digitalWrite(_motor_step_2, LOW);
			digitalWrite(_motor_enable_2, HIGH);    
		}
		else if(step_size == 16)
		{
			//sets speed
			current_control(16);
			
			digitalWrite(_motor_ms_21, HIGH);    
			digitalWrite(_motor_ms_22, HIGH);    
			digitalWrite(_motor_ms_23, HIGH);
			
			digitalWrite(_motor_enable_2, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				digitalWrite(_motor_step_2, HIGH);
				delayMicroseconds(step16); //low time
				digitalWrite(_motor_step_2, LOW);
				delayMicroseconds(step16); // high time
			}
			digitalWrite(_motor_step_2, LOW);
			digitalWrite(_motor_enable_2, HIGH);   
		}
		else Serial.println("error: incorrect value for step_size"); //print error code
	}
	
	if(motnum == 3)
	{
		// sets direction of rotation
		int dir = (number_of_steps > 0) ? HIGH : LOW;
		number_of_steps = abs(number_of_steps);
		
		digitalWrite(_motor_dir_3, dir);
		
		// check to see what setp size was selected
		if(step_size == 1)
		{
			//sets speed
			current_control(1);
			
			digitalWrite(_motor_ms_31, LOW);    
			digitalWrite(_motor_ms_32, LOW);    
			digitalWrite(_motor_ms_33, LOW);
			
			digitalWrite(_motor_enable_3, LOW);    // enable motor 1
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				digitalWrite(_motor_step_3, HIGH);
				delayMicroseconds(step1); //high time
				digitalWrite(_motor_step_3, LOW);
				delayMicroseconds(step1); //low time
			}
			digitalWrite(_motor_step_3, LOW);
			digitalWrite(_motor_enable_3, HIGH);    // disable motor 1
		}
		
		else if(step_size == 2)
		{
			//sets speed
			current_control(2);
			
			digitalWrite(_motor_ms_31, HIGH);    
			digitalWrite(_motor_ms_32, LOW);    
			digitalWrite(_motor_ms_33, LOW);
			
			digitalWrite(_motor_enable_3, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				digitalWrite(_motor_step_3, HIGH);
				delayMicroseconds(step2); //low time
				digitalWrite(_motor_step_3, LOW);
				delayMicroseconds(step2); // high time
			}
			digitalWrite(_motor_step_3, LOW);
			digitalWrite(_motor_enable_3, HIGH);    
		}
		
		else if(step_size == 4)
		{
			//sets speed
			current_control(4);
			
			digitalWrite(_motor_ms_31, LOW);    
			digitalWrite(_motor_ms_32, HIGH);    
			digitalWrite(_motor_ms_33, LOW);
			
			digitalWrite(_motor_enable_3, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				digitalWrite(_motor_step_3, HIGH);
				delayMicroseconds(step4); //low time
				digitalWrite(_motor_step_3, LOW);
				delayMicroseconds(step4); // high time
			}
			digitalWrite(_motor_step_3, LOW);
			digitalWrite(_motor_enable_3, HIGH);    
		}
		else if(step_size == 8)
		{
			//sets speed
			current_control(8);
			
			digitalWrite(_motor_ms_31, HIGH);    
			digitalWrite(_motor_ms_32, HIGH);    
			digitalWrite(_motor_ms_33, LOW);
			
			digitalWrite(_motor_enable_3, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				digitalWrite(_motor_step_3, HIGH);
				delayMicroseconds(step8); //low time
				digitalWrite(_motor_step_3, LOW);
				delayMicroseconds(step8); // high time
			}
			digitalWrite(_motor_step_3, LOW);
			digitalWrite(_motor_enable_3, HIGH);    
		}
		else if(step_size == 16)
		{
			//sets speed
			current_control(16);
			
			digitalWrite(_motor_ms_31, HIGH);    
			digitalWrite(_motor_ms_32, HIGH);    
			digitalWrite(_motor_ms_33, HIGH);
			
			digitalWrite(_motor_enable_3, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				digitalWrite(_motor_step_3, HIGH);
				delayMicroseconds(step16); //low time
				digitalWrite(_motor_step_3, LOW);
				delayMicroseconds(step16); // high time
			}
			digitalWrite(_motor_step_3, LOW);
			digitalWrite(_motor_enable_3, HIGH);   
		}
		else Serial.println("error: incorrect value for step_size"); //print error code
	}
	
	if(motnum == 4)
	{
		// sets direction of rotation
		int dir = (number_of_steps > 0) ? HIGH : LOW;
		number_of_steps = abs(number_of_steps);

		digitalWrite(_motor_dir_4, dir);

		// check to see what setp size was selected
		if(step_size == 1)
		{
			//sets speed
			current_control(1);
			
			digitalWrite(_motor_ms_41, LOW);    
			digitalWrite(_motor_ms_42, LOW);    
			digitalWrite(_motor_ms_43, LOW);
			
			digitalWrite(_motor_enable_4, LOW);   
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				digitalWrite(_motor_step_4, HIGH);
				delayMicroseconds(step1); 
				digitalWrite(_motor_step_4, LOW);
				delayMicroseconds(step1); 
			}
			digitalWrite(_motor_step_4, LOW);
			digitalWrite(_motor_enable_4, HIGH);    
		}

		else if(step_size == 2)
		{
			//sets speed
			current_control(2);
			
			digitalWrite(_motor_ms_41, HIGH);    
			digitalWrite(_motor_ms_42, LOW);    
			digitalWrite(_motor_ms_43, LOW);
			
			digitalWrite(_motor_enable_4, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				digitalWrite(_motor_step_4, HIGH);
				delayMicroseconds(step2); 
				digitalWrite(_motor_step_4, LOW);
				delayMicroseconds(step2); 
			}
			digitalWrite(_motor_step_4, LOW);
			digitalWrite(_motor_enable_4, HIGH);    
		}

		else if(step_size == 4)
		{
			//sets speed
			current_control(4);
			
			digitalWrite(_motor_ms_41, LOW);    
			digitalWrite(_motor_ms_42, HIGH);    
			digitalWrite(_motor_ms_43, LOW);
			
			digitalWrite(_motor_enable_4, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				digitalWrite(_motor_step_4, HIGH);
				delayMicroseconds(step4); 
				digitalWrite(_motor_step_4, LOW);
				delayMicroseconds(step4); 
			}
			digitalWrite(_motor_step_4, LOW);
			digitalWrite(_motor_enable_4, HIGH);    
		}
		else if(step_size == 8)
		{
			//sets speed
			current_control(8);
			
			digitalWrite(_motor_ms_41, HIGH);    
			digitalWrite(_motor_ms_42, HIGH);    
			digitalWrite(_motor_ms_43, LOW);
			
			digitalWrite(_motor_enable_4, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				digitalWrite(_motor_step_4, HIGH);
				delayMicroseconds(step8); 
				digitalWrite(_motor_step_4, LOW);
				delayMicroseconds(step8); 
			}
			digitalWrite(_motor_step_4, LOW);
			digitalWrite(_motor_enable_4, HIGH);    
		}
		else if(step_size == 16)
		{
			//sets speed
			current_control(16);
			
			digitalWrite(_motor_ms_41, HIGH);    
			digitalWrite(_motor_ms_42, HIGH);    
			digitalWrite(_motor_ms_43, HIGH);
			
			digitalWrite(_motor_enable_4, LOW);    
			for(int i=1;i<=number_of_steps;i++)
			{
				//low to high transition moves one step
				digitalWrite(_motor_step_4, HIGH);
				delayMicroseconds(step16); 
				digitalWrite(_motor_step_4, LOW);
				delayMicroseconds(step16); 
			}
			digitalWrite(_motor_step_4, LOW);
			digitalWrite(_motor_enable_4, HIGH);   
		}
		else Serial.println("error: incorrect value for step_size"); //print error code
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

void quadstep::current_control(int step)
{
	if(step == 1)
	{
		step1 = STEPMIN + (_torque * 260);
	}
	else if(step == 2)
	{
		step2 = (STEPMIN + (_torque * 260)) / 2;
	}
	else if(step == 4)
	{
		step4 = (STEPMIN + (_torque * 260)) / 4;
	}
	else if(step == 8)
	{
		step8 = (STEPMIN + (_torque * 260)) / 8;
	}
	else if(step == 16)
	{
		step16 = (STEPMIN + (_torque * 260)) / 16;
	}
}
