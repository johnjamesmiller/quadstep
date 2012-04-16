/*

	created by Aaron Weiss, SparkFun electronics 2011
	
	Beerware - do what you wish with this ish

*/

#ifndef quadstep_h
#define quadstep_h

#include "WProgram.h"
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
	void motor_pins(int motnum,int motor_enable,int motor_dir,int motor_ms1, int motor_ms2, int motor_ms3, int motor_step);
    void motor_go(int motnum, step_modes_t step_size, int number_of_steps, int torque);
	void stall(int motnum);
	//void motor1rpm(int direction,int level);
 
  private:
	void current_control(step_modes_t step_size);
	int _torque;
	int step;
	
	int _motor_enable_1;
	int _motor_dir_1;
	int _motor_step_1;
	int _motor_ms_11;
	int _motor_ms_12;
	int _motor_ms_13;
	
	int _motor_enable_2;
	int _motor_dir_2;
	int _motor_step_2;
	int _motor_ms_21;
	int _motor_ms_22;
	int _motor_ms_23;
	
	int _motor_enable_3;
	int _motor_dir_3;
	int _motor_step_3;
	int _motor_ms_31;
	int _motor_ms_32;
	int _motor_ms_33;
	
	int _motor_enable_4;
	int _motor_dir_4;
	int _motor_step_4;
	int _motor_ms_41;
	int _motor_ms_42;
	int _motor_ms_43;
};
#endif
