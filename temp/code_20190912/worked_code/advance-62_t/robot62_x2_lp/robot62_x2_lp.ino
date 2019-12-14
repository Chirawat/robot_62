#include "stdrobot.h"
int SPEED           = 50;
int WALL_DELAY      = 100;
int BACKWARD_DELAY  = 300;
int TURN_L_DELAY      = 1250;
int TURN_R_DELAY      = 1250;

void BK1(){
  ao(); delay(100);
  bk(SPEED); delay(BACKWARD_DELAY*2);
  ao(); delay(100);
}

void FF2(){
  ao(); delay(100);
  fd(SPEED); delay(BACKWARD_DELAY*4);
  ao(); delay(100);
}
void FF1(){
  ao(); delay(100);
  fd(SPEED); delay(BACKWARD_DELAY*2);
  ao(); delay(100);
}
void setup() {
  robot_init();
  Serial.begin(115200);
  OK();

   FF();FR();
   FF();FR();
   FF();FR();
   FF();FL();
   FF();
   BK1();
   FL();
   FF2(); 
   FF();
   FL();FF();
   BK1();FR();FF();
   FL();
   FF();
   FR();FF();
   FR();FF();

  

  // Tan make it
  //FF();FR();FF();FR();FF();FR();FF();FL();
  //FF();FL();FL();FF1();FR();
  
}

void loop() {
  Serial.print("A0=");
  Serial.print(in(A0));
  Serial.print(", A1=");
  Serial.print(in(A1));
  Serial.print(", A2=");
  Serial.print(in(A2));
  Serial.println();
  delay(500);
}
