#include "stdrobot.h"



void setup() {
  robot_init();
  Serial.begin(115200);
  OK();
  //FF();FR();FF();FR();FF();FR();FF();FL();
//  FF();FL();FL();
  
}

void loop() {
//  Serial.print("A0=");
//  Serial.print(in(A0));
//  Serial.print(", A1=");
  Serial.print(in(A3)); Serial.print(",");
//  Serial.print(", A2=");
//  Serial.print(in(A2));
//  Serial.print(", A3=");
  Serial.println(in(A1));
//  Serial.println();
  delay(50);
}
