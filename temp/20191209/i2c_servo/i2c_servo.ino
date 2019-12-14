#include <Wire.h>
#include <Servo.h>  

//int sdata[10] = {0xAA, 0x01, 0x02, 80};
int sdata[10];

#define SERVO_CMD 0x01
Servo servo_pin_2;
Servo servo_pin_3;
Servo servo_pin_4;
Servo servo_pin_5;
Servo servo_pin_6;

void setup()
{
  servo_pin_2.attach(2);
  servo_pin_3.attach(3);
  servo_pin_4.attach(4);
  servo_pin_5.attach(5);
  servo_pin_6.attach(6);
  
  Serial.begin(9600); 
  
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
}

void loop()
{
//  servo_lp(4, 80);
//  delay(500);
//  servo_lp(4, 110);
//  delay(500);
}

void receiveEvent(int howMany)
{
  int length=0;
  while(Wire.available()) // loop through all but the last
  {
    int c = Wire.read(); // receive byte as a character
    sdata[length++] = c;
  }
  ////////////////////
  if(sdata[0]==0xAA){
    int cmd = sdata[1];
    switch(cmd){
      case SERVO_CMD:
        int ch = sdata[2];
        int angle = sdata[3];
        servo_lp(ch, angle);
        break;
    }
  }
}

void servo_lp(int ch, int angle){
  switch(ch){
    case 1: 
      servo_pin_2.write( angle );
      break;
    case 2:
      servo_pin_3.write( angle );
      break;
    case 3:
      servo_pin_4.write( angle );
      break;
    case 4:
      servo_pin_5.write( angle );
      break;
    case 5:
      servo_pin_6.write( angle );
      break;
  }
}
