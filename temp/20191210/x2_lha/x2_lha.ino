#include <popx2.h>
#include <Wire.h>

#define YELLOW  1
#define RED     2
#define GREEN   3
#define BLUE    4
#define WHITE   5

#define FrontL (analog(1)>300)
#define FrontR (analog(3)>300)
#define L (analog(0)>300)
#define R (analog(2)>300)

int SPEED = 35;
byte x = 0;
int l_passed = 0;
int r_passed = 0;

bool finished = false;

void FF(){
  fd(SPEED);
  /////////////////////////////////////
  while(FrontL && FrontR){
    if(!L){
      sr(SPEED); delay(50);
    }
    else if(!R){
      sl(SPEED); delay(50);
    }
    else{
      fd(SPEED);
    }
  }

  /////////////////////////////////////
  while(L || R){
    if(!L && r_passed==0){
      tl(SPEED);
      l_passed = 1;
    }
    if(!R && l_passed==0){
      tr(SPEED);
      r_passed = 1;
    }
  }
  l_passed = 0;
  r_passed = 0;
  ao(); delay(500);
  /////<<<<<<<<<<<<<<<<<<<
  bk(SPEED); delay(250);
  ao(); delay(250);

  int color = getColor();
  
  switch(color){
    case BLUE:
    case GREEN:
      fd(SPEED);
      delay(250);
      while(!L || !R)
        delay(10);
      ao(); delay(250);
      break;
  }  
  
//  bk(SPEED); delay(250);
//  ao(); delay(250);
  
  color = getColor();
  
  switch(color){
    case RED:
      sl(SPEED); delay(1450);
      ao(); delay(250);
      kick(1);
      break;
    case YELLOW:
      sl(SPEED); delay(1450);
      ao(); delay(250);
      kick(2);
      break;
    case BLUE:
      sl(SPEED); delay(1450);
      ao(); delay(250);
      kick(3);
      break;
    case GREEN:
      sl(SPEED); delay(1450);
      ao(); delay(250);
      kick(4);
      break;
  }
} 

void FR(){
  sr(SPEED); delay(750);
  ao();  delay(250);
}

void FL(){
  sl(SPEED); delay(750);
  ao();  delay(250);
}

void servo_lp(int ch, int angle){
  Wire.beginTransmission(4);  // transmit to device #4
  Wire.write(0xAA);           
  Wire.write(0x01);
  Wire.write(ch);
  Wire.write(angle);
  Wire.endTransmission();    // stop transmitting
}

int getColor(){
  beep();
  Wire.requestFrom(4,1);
  while(Wire.available()){
    int c =  Wire.read();  
    setTextSize(3); 
    switch(c){
      case YELLOW:
        glcd(1,1, "YELLOW");
        break;
      case RED: 
        glcd(1,1, "RED");
        break;
      case GREEN:
        glcd(1,1, "GREEN");
        break;
      case BLUE:
        glcd(1,1, "BLUE");
        break;
      case WHITE:
        glcd(1,1, "WHITE");
        break;
    }
    return c;
  }
  return false;
}

void robot_init(){
  servo_lp(1, 90);
  servo_lp(2, 90);
  servo_lp(3, 90);
  servo_lp(4, 90);
  servo_lp(5, 90);
}

void kick(int ch){
  servo_lp(ch, 70); delay(500);
  servo_lp(ch, 90);
}

void LHA(){
  while(!finished){
    FF();
    FR();
  }
}

void FF_t(){
  while(in(30)){
    fd(SPEED);
  }
  ao();
}
void setup(){
  Serial.begin(9600);
  Wire.begin();          
  robot_init();
  glcd(1,1, "OK");
  OK();
  ///////////////////////////////////////////
  //LHA();
}

void loop(){
}
