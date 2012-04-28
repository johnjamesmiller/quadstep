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
    void go(step_modes_t step_size, int number_of_steps, int torque);
	void stall();
	void set_enable_pin(int enable_pin);
	void set_direction_pin(int direction_pin);
	void set_step_pin(int step_pin);
	void set_microstep_select_pins(int ms1_pin,int ms2_pin,int ms3_pin);
	//void motor1rpm(int direction,int level);
 
  private:
	void set_direction(int number_of_steps);
	void set_speed(step_modes_t step_size, int torque);
	void set_microstep_format(step_modes_t step_size);
	void enable();
	void step();
	void disable();
	int pulse_width;
	int _enable_pin;
	int _direction_pin;
	int _step_pin;
	int _ms1_pin;
	int _ms2_pin;
	int _ms3_pin;
};
#endif
