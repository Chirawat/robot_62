#include <Servo.h>	
Servo servo_pin_2;
void setup() {
  servo_pin_2.attach(2,530,2600);
}

void loop() {
  servo_pin_2.write( 0 );
  delay( 2000 );
  servo_pin_2.write( 180 );
  delay( 2000 );
  servo_pin_2.write( 0 );
  delay( 2000 );
  servo_pin_2.write( 180 );
  delay( 1000 );
}
