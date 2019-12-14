#include <Servo.h>	
Servo servo_pin_2;
Servo servo_pin_3;
Servo servo_pin_4;
Servo servo_pin_5;
Servo servo_pin_6;

void setup() {
  servo_pin_2.attach(2);
  servo_pin_3.attach(3);
  servo_pin_4.attach(4);
  servo_pin_5.attach(5);
  servo_pin_6.attach(6);
/*
  servo_pin_2.write( 0 );
  servo_pin_3.write( 0 );
  servo_pin_4.write( 0 );
  servo_pin_5.write( 0 );
  servo_pin_6.write( 0 );
*/
}

void loop() {

  servo_pin_2.write( 110 );
  servo_pin_3.write( 110 );
  servo_pin_4.write( 110 );
  servo_pin_5.write( 110 );
  servo_pin_6.write( 110 );
  delay( 2000 );
  
  servo_pin_2.write( 80 );
  servo_pin_3.write( 80 );
  servo_pin_4.write( 80 );
  servo_pin_5.write( 80 );
  servo_pin_6.write( 80 );
  delay( 2000 );
}
