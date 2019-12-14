#include <Wire.h>
#include <Servo.h>  

#define YELLOW  1
#define RED     2
#define GREEN   3
#define BLUE    4
#define WHITE   5

//const int outputEnabled = 2; // write LOW to turn on Note, may not be hooked up.
const int s0 = 7; // sensor pins
const int s1 = 8;
const int s2 = 9;
const int s3 = 10;
const int nLED = 11; // illuminating LED
const int out = 12; // TCS230 output

// variables to store color values
int red = 0;
int green = 0;
int blue = 0;


//int sdata[10] = {0xAA, 0x01, 0x02, 80};
int sdata[10];

#define SERVO_CMD 0x01
Servo servo_pin_2;
Servo servo_pin_3;
Servo servo_pin_4;
Servo servo_pin_5;
Servo servo_pin_6;

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

void setup(){
  servo_pin_2.attach(2);
  servo_pin_3.attach(3);
  servo_pin_4.attach(4);
  servo_pin_5.attach(5);
  servo_pin_6.attach(6);
  
//  Serial.begin(9600); 
  
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent);

  // Configure RGB sensor
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(nLED, OUTPUT);
  pinMode(out, INPUT);
  
  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);
  digitalWrite(nLED, LOW);

  
}


void color() {
  digitalWrite(nLED,1);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  
  // count OUT, pRed, RED
  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s3, HIGH);
  
  //count OUT, pBLUE, BLUE
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s2, HIGH);
  
  // count OUT, pGreen, GREEN
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(nLED,0);
}

void loop(){
//  requestEvent();
//  delay(500);
}

void requestEvent()
{
  Serial.println("getting color....");
  color();
  Serial.print("R");
  Serial.print(red, DEC);
  Serial.print(" G");
  Serial.print(green, DEC);
  Serial.print(" B");
  Serial.print(blue, DEC);
  Serial.println();
//  Serial.println();

  
  Serial.print("Color: ");
  if( abs(green-red)<=2 && abs(green-blue)<=2 ){
    Serial.println("White");
    Wire.write(WHITE);
  }
  else if (blue > red && blue > green){
    Serial.println("Yellow");
    Wire.write(YELLOW);
  }
  else if (red < blue && red < green){ 
    Serial.println("Red");
    Wire.write(RED);
  }
  else if (blue < red && blue < green) {
    Serial.println("blue");
    Wire.write(BLUE);
  }
  else {
    Serial.println("green");
    Wire.write(GREEN);
  }
  
  
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
