#include "stdrobot.h"

int SPEED = 40;
void setup() {
  robot_init();
  OK();  
  delay;(1000);
//  ////////////////
//  
  FF();FF();FF();FL();FF();
  FR();FF();FF();FR();FF();
  FR();FF();
  ao();


  
  //FF();FR();FF();FF();
  //FL();FF();FF();

  
  //FF();FF();FL();FF();FR();FF();FF();FR();FF();FR();FF();

//  FF();FF();
//  FL();FF();
//  FR();FF();FF();
//  FR();FF();FR();FF();

//FF();FL();FF();
//FR();FF();FF();FF();
//FR();FF();FF();FF();FF();
//FR();FF();FR();FF();

  
}

void loop() {
  //read_sensor();
  //follow_line();
}
