/*

	created by Aaron Weiss, SparkFun electronics 2011
	
	Beerware - do what you wish with this ish

*/

#ifndef quadstep_h
#define quadstep_h

#include "WProgram.h"


/*
 * Microstep Resolution		Excitation Mode
 * Full Step 				2 Phase
 * Half Step 				1-2 Phase
 * Quarter Step 			W1-2 Phase
 * Eighth Step 				2W1-2 Phase
 * Sixteenth Step 			4W1-2 Phase
 */

enum step_modes_t {
	FULL = 1,
	HALF = 2,
	QUARTER = 4,
	EIGHTH = 8,
	SIXTEENTH = 16
};

class quadstep
{
  public:
	quadstep();
	void motor_pins(int motor_enable,int motor_dir,int motor_ms1, int motor_ms2, int motor_ms3, int motor_step);
    void go(step_modes_t step_size, int number_of_steps, int torque);
	void stall();
	//void motor1rpm(int direction,int level);
 
  private:
	void set_speed(step_modes_t step_size);
	void set_microstep_format(step_modes_t step_size);
	void set_direction(int number_of_steps);
	void step();
	void enable();
	void disable();
	int _torque;
	int pulse_width;
	
	int _motor_enable;
	int _motor_dir;
	int _motor_step;
	int _motor_ms1;
	int _motor_ms2;
	int _motor_ms3;
};
#endif
