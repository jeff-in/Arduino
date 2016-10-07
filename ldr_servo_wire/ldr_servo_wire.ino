#include <Servo.h>

float current_pos;
float target_pos;


float easing = 0.7;


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
   ldr = map( ldr, 10,265, 600, 2400);

  
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



