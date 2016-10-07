/*
Code to drive a servo with an easing function
*******************************************************************
Date 05-10-2016
Jeffin Philip
-----------------------
Description:
The code uses the analog input from a sensor( An LDR in this project) and map the analog values
to angle of rotation for the servo.
------------------------------------------
To get a high resolution movement and a smoother rotation the servo rotation is being calculated in
milliseconds (0-2400) instead of degrees(0-180). The code also uses an easing fuction to reduce the speed of
rotation at the end of movement to avoid any kind of stagger. The easing value is read through a potentiometer 
and converted into a multiplier value (divided by 1000) . The movement is done in decremental steps, where each step is
multiplied by the easing value.
*****************************************************
eg: for rotation form 10 to 100 degrees.    //The example uses degrees instead of milliseconds, but the code uses milliseconds for angles
angle of rotation=90
if pot input is 500, easing value is .5
sp 90 degree movement will be executed as
45--------------- (90*0.5)
22.5--------------((90-(45)*0.5)
11.25-------------((90-(45+22.5))*0.5)
5.625
2.8125
.
.etc.
********************************************************
This movement will reduce the stagger in servo movement.

*/
#include <Servo.h>

float current_pos;
float target_pos;


float easing = 0.7;//The starting value for the easing function, 0<easing<1


Servo motor;


void setup() {
  Serial.begin(9600);
    current_pos=1500;
   motor.attach(4);

}

void loop() {
   int ldr;   // target 
   int pot; // easing
   float diff; 

 
   ldr = analogRead(A2);// range 600 2400
   Serial.println(ldr);
   ldr = map( ldr, 10,265, 600, 2400);// Potentiometer used in circuit for better control

  
   pot = analogRead(A3);
   pot = map( pot, 0, 1023, 0,1000);
   easing = (float)pot;
   easing /= 1000;
  
   target_pos = (float)ldr;
   diff = target_pos - current_pos;
  
  
   if( diff != 0.00 ) {
      current_pos += diff * easing;
   } else {
     
   }
  
   motor.writeMicroseconds( (int)current_pos );
   delay(100);
  
}



