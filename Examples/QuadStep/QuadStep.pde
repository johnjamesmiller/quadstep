/*
  SparkFun Electronics 2011
  Aaron Weiss, aaron at sparkfun dot com
  Beer-ware License: You can do whatever you want with this sketch.
                     If we meet someday, you can buy me a beer.
                     
  QuadSetpper Example Sketch. For use with a 1.8 degree bipolar stepper motor.

  Library Usage: 
  
  motor_pins(y,z,l,m,n,o)
  y: enable pin assignment
  z: direction pin assignment
  l: MS1 pin assignment
  m: MS2 pin assignment
  n: MS3 pin assignment
  o: step pin
  
  motor_go(y,z,l)
  y: step size: 1, 2, 4, 8, or 16
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
  motor1.motor_pins(0,1,2,3,4,9); //ch 1
  motor2.motor_pins(7,6,A0,A1,A2,5);      //ch 2
  motor3.motor_pins(12,13,A0,A1,A2,10);  //ch 3
  motor4.motor_pins(4,27,A0,A1,A2,11);  //ch 4
}

//1.8deg = 1step
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
