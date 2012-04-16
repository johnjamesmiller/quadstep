/*
  SparkFun Electronics 2011
  Aaron Weiss, aaron at sparkfun dot com
  Beer-ware License: You can do whatever you want with this sketch.
                     If we meet someday, you can buy me a beer.
                     
  QuadSetpper Example Sketch. For use with a 1.8 degree bipolar stepper motor.

  Library Usage: 
  
  motor_pins(x,y,z,l,m,n,o)
  x: motor channel number
  y: enable pin assignment
  z: direction pin assignment
  l: MS1 pin assignment
  m: MS2 pin assignment
  n: MS3 pin assignment
  o: step pin
  
  motor_go(x,y,z,l)
  x: motor channel number
  y: step size: 1, 2, 4, 8, or 16
  z: increments for given step size
     for full step: 1 increment = 1.8deg
     for half step: 1 increment = 0.9deg and so on
     negaitve numbers rotate in the opposite direction
  l: torque/speed (0-10), 0 is high speed/low torque/low current
                          10 is low speed/high torque/high current (2.0A max)
                      
  stall(x)
  x: motor channel number
*/

// include the motor library
#include <quadstep.h>

// create an instance of the class motor
quadstep quadstep;

void setup() {
  // assign the pin connections
  quadstep.motor_pins(1,0,1,2,3,4,9); //ch 1
  quadstep.motor_pins(2,7,6,A0,A1,A2,5);      //ch 2
  quadstep.motor_pins(3,12,13,A0,A1,A2,10);  //ch 3
  quadstep.motor_pins(4,4,27,A0,A1,A2,11);  //ch 4
 
}

//1.8deg = 1step
void loop() {
  
  // step motor 2 for 200 increments CW
  quadstep.motor_go(2,1,-200,2);
  delay(500);
  // step motor 2 for 200 increments CCW
  quadstep.motor_go(2,1,200,2);
  delay(500);
 
  // holds the motor in one position with full torque/current
  //motor.stall(2);
  //delay(500); 
}
