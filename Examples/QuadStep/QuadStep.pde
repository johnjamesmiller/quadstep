/*
  SparkFun Electronics 2011
  Aaron Weiss, aaron at sparkfun dot com
  Beer-ware License: You can do whatever you want with this sketch.
                     If we meet someday, you can buy me a beer.
                     
  QuadSetpper Example Sketch. For use with a stepper motor.

  Library Usage: 

  set_enable_pin(enable_pin)
  set_direction_pin(direction_pin)
  set_step_pin(step_pin)
  set_microstep_select_pins(ms1_pin,ms2_pin,ms3_pin)

  go(y,z,l)
  y: step size: FULL, HALF, QUARTER, EIGHTH, or SIXTEENTH
  z: increments for given step size
     for full step: 1 increment = 1.8deg
     for half step: 1 increment = 0.9deg and so on
     negaitve numbers rotate in the opposite direction
  l: torque/speed (0-10), 0 is high speed/low torque/low current
                          10 is low speed/high torque/high current (2.0A max)
  stall()
*/

// include the motor library
#include <quadstep.h>

// create an instance of the class motor
quadstep motor1;
quadstep motor2;
quadstep motor3;
quadstep motor4;

void setup() {
  // assign the pin connections
  motor1.set_enable_pin(0);
  motor1.set_direction_pin(1);
  motor1.set_step_pin(9);
  motor1.set_microstep_select_pins(2,3,4);
  
  motor2.set_enable_pin(7);
  motor2.set_direction_pin(6);
  motor2.set_step_pin(5);
  motor2.set_microstep_select_pins(A0,A1,A2);
  
  motor3.set_enable_pin(12);
  motor3.set_direction_pin(13);
  motor3.set_step_pin(10);
  motor3.set_microstep_select_pins(A0,A1,A2);
  
  motor4.set_enable_pin(4);
  motor4.set_direction_pin(27);
  motor4.set_step_pin(11);
  motor4.set_microstep_select_pins(A0,A1,A2);
}

void loop() {
  
  // step motor 2 for 200 increments CW
  motor2.go(FULL,-200,2);
  delay(500);
  // step motor 2 for 200 increments CCW
  motor2.go(FULL,200,2);
  delay(500);
 
  // holds the motor in one position with full torque/current
  //motor.stall();
  //delay(500); 
}
