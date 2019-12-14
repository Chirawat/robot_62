#include <popx2.h>
#include <Wire.h>
#define TURN180 1200  
#define TURN180_BLUE 1400
#define TURN90  750
#define POR 2000  // แยกยาว แยกสั้น (ยาว ข / สั้น ซ)

#define YELLOW  1
#define RED     2
#define GREEN   3
#define BLUE    4
#define WHITE   5

#define FrontL (analog(1)>300)
#define FrontR (analog(3)>300)
#define L (analog(0)>300)
#define R (analog(2)>300)
#define CAM (in(30))

int SPEED = 35;
byte x = 0;
int l_passed = 0;
int r_passed = 0;

bool finished = false;
bool dest = false;

void FF(){
  int color;
  //fd(SPEED);
  fd2(SPEED, SPEED*0.8);
  /////////////////////////////////////
  while(FrontL && FrontR){
    if(!L){
      sr(SPEED); delay(50);
    }
    else if(!R){
      sl(SPEED); delay(50);
    }
    else{
      //fd(SPEED);
      fd2(SPEED, SPEED*0.8);
    }
  }
  /////////////////////////////////////
  while( (L&&l_passed==0) || (R&&r_passed==0)){
    if(!L){
      tl(SPEED);
      l_passed = 1;
    }
    if(!R){
      tr(SPEED);
      r_passed = 1;
    }
  }
  l_passed = 0;
  r_passed = 0;
  ao(); delay(500);
  
  color = getColor();

  if(color==BLUE || color==GREEN){
    fd2(SPEED, SPEED*0.8); delay(200);
    ao(); delay(250);
    sl(SPEED); delay(TURN180_BLUE);
    ao(); delay(250);
    if(color==BLUE)
      kick(4);
    else if(color==GREEN)
      kick(3);
//    while(1);
  }
  
  bk(SPEED); delay(200);       /////<<<<<<<<<<<<<<<<<<< ถอยหลัง
  ao(); delay(250);

  color = getColor();
  
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
  
  switch(color){
    case RED:
      sl(SPEED); delay(TURN180);
      ao(); delay(250);
      fd2(SPEED, SPEED*0.8); delay(200);
      ao();
      kick(1);
      //while(1);
      break;
    case YELLOW:
      sl(SPEED); delay(TURN180);
      ao(); delay(250);
      kick(2);
      break;
    case BLUE:
      sl(SPEED); delay(TURN180);
      ao(); delay(250);
      kick(3);
      break;
    case GREEN:
      sl(SPEED); delay(TURN180);
      ao(); delay(250);
      kick(4);
      break;
  }
} 

void FR(){
  sr(SPEED); delay(TURN90);
  ao();  delay(250);
}

void FL(){
  sl(SPEED); delay(TURN90);
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
  servo_lp(ch, 60); delay(500);
  servo_lp(ch, 90); delay(500);
  
  servo_lp(ch, 50); delay(500);
  servo_lp(ch, 90); delay(500);
  
  servo_lp(ch, 45); delay(500);
  servo_lp(ch, 90); delay(500);

  servo_lp(ch, 45); delay(500);
  servo_lp(ch, 90); delay(500);

  dest = true;
}

void LHA(){
  unsigned long previousMillis = 0;
  unsigned long currentMillis = 0;
  unsigned long interval = 0;
  currentMillis = millis();
  while(!finished){
    previousMillis = millis();;
    FF();
    currentMillis = millis();
    interval = currentMillis - previousMillis;
    glcdClear();
    glcd(2,1,"%d", (int)(currentMillis - previousMillis));
    if(!dest){
      if(interval<POR){
        FL();
      }
      else{
        FR();
      }
    }
    dest = false;
  }
}

void setup(){
  bool serviceMode;
  Serial.begin(9600);
  Wire.begin();          
  robot_init();
  setTextSize(3); 
  
  if(sw_OK()) 
    serviceMode=true ;
  else 
    serviceMode=false;
  if(serviceMode)
    glcd(1,1,"Service");
    
  while(serviceMode){
    fd(SPEED); delay(500);
    sl(SPEED); delay(500);
    ao();
    kick(1);
    kick(2);
    kick(3); 
    kick(4); 
    kick(5); 
  }
  
  
  
  OK();
  ///////////////////////////////////////////
  LHA();
}

void loop(){
}
