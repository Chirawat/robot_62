#include <popx2.h>
#include <Wire.h>

#define YELLOW  1
#define RED     2
#define GREEN   3
#define BLUE    4

byte x = 0;

void servo_lp(int ch, int angle){
  Wire.beginTransmission(4); // transmit to device #4
  Wire.write(0xAA);        // sends five bytes
  Wire.write(0x01);
  Wire.write(ch);
  Wire.write(angle);
  Wire.endTransmission();    // stop transmitting
}

int getColor(){
  Wire.requestFrom(4,1);
  while(Wire.available())  
  {
    int c =  Wire.read();  
    return c;
  }
  return false;
}


void setup(){
  Serial.begin(9600);
  Wire.begin();                 // join i2c bus (address optional for master)
}

void loop(){
  //servo_lp(2, 80); delay(500);
  //servo_lp(2, 110); delay(500);
  //Serial.println("requested...");
  
  getColor();
  delay(500);
}
