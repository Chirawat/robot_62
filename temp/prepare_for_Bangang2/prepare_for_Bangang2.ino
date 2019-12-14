#include "stdrobot.h"
int SPEED = 45;
void setup() {
  robot_init();
  OK();  
  delay;(1000);
  ////////////////

//  FF();FF();
//  FL();FF();
//  FR();FF();FF();
//  FR();FF();FR();FF();

FF();FL();FF();
FR();FF();FF();FF();
FR();FF();FF();FF();FF();
FR();FF();FR();FF();

  
}

void loop() {
}
