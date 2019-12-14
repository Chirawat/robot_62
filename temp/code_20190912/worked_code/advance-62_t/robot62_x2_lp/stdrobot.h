// stdrobot.h
#ifndef stdrobot_h
#define stdrobot_h

#include "pin_mapping_xt.h"
//#include <Servo.h>


extern int SPEED;
extern int WALL_DELAY;       // มุมเลี้ยวชนผนัง
extern int BACKWARD_DELAY;
extern int TURN_L_DELAY;
extern int TURN_R_DELAY;

#define STRAING_DELAY 10
#define in(port) readSensor(port)


int L1, L2, R1, R2;
extern int SPEED;

int readSensor(int port){
  int val=analogRead(port);
  return val>200 ? 1:0;
//  return val;
}

void beep(){
  tone(buzzer, 1500);
  delay(50);
  noTone(buzzer);
}

void OK(){
	while(digitalRead(SW_OK))
		delay(100);
}

void fd(int speed){
  //directiovoin
  digitalWrite(ADIR, LOW);
  digitalWrite(BDIR, LOW);
  // speed
  analogWrite(PWMA, map(speed, 0, 100, 0, 255));
  analogWrite(PWMB, map(speed, 0, 100, 0, 255));
}

void sl(int speed){
  //direction
  digitalWrite(ADIR, HIGH);
  digitalWrite(BDIR, LOW);
  // speed
  analogWrite(PWMA, map(speed, 0, 100, 0, 255));
  analogWrite(PWMB, map(speed, 0, 100, 0, 255));
}

void sr(int speed){
  //direction
  digitalWrite(ADIR, LOW);
  digitalWrite(BDIR, HIGH);
  // speed
  analogWrite(PWMA, map(speed, 0, 100, 0, 255));
  analogWrite(PWMB, map(speed, 0, 100, 0, 255));
}

void tl(int speed){
  //direction
  digitalWrite(ADIR, HIGH);
  digitalWrite(BDIR, LOW);
  // speed
  analogWrite(PWMA, 0);
  analogWrite(PWMB, map(speed, 0, 100, 0, 255));
}

void tr(int speed){
  //direction
  digitalWrite(ADIR, LOW);
  digitalWrite(BDIR, HIGH);
  // speed
  analogWrite(PWMA, map(speed, 0, 100, 0, 255));
  analogWrite(PWMB, 0);
}

void bk(int speed){
  //direction
  digitalWrite(ADIR, HIGH);
  digitalWrite(BDIR, HIGH);
  
  // speed
  analogWrite(PWMA, map(speed, 0, 100, 0, 255));
  analogWrite(PWMB, map(speed, 0, 100, 0, 255));
}

void ao(){
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
}

///////////////////////////////////

void FF() {
  /////////// เช็คผนัง /////////////
  while (in(A1)) {          
    if (!in(A0)) {
      ao(); delay(100);
      bk(SPEED); delay(100);
      sr(SPEED); delay(100);
      //delay(WALL_DELAY);
    }
    if (!in(A2)) {
      ao(); delay(100);
      bk(SPEED); delay(100);
      sl(SPEED); delay(100);
      //delay(WALL_DELAY);
    }
    if(in(A0)&&in(A2)) {
      fd(SPEED);
    }
  }
  //beep();beep();
  //ao();while(1);
  //////////// เช็คแยกแล้วตั้งลำ ///////////////
  ao();delay(100);
  bk(SPEED*0.75); delay(250);
  //fd(SPEED*0.25);
  int a0=0;
  int a1=0;
  while (!a0 || !a1) {
    if (!in(A0)) {
      sl(SPEED);
      a0 = 1;
    }
    else if (!in(A2)) {
      sr(SPEED);
      a1 = 1;
    }
    else{
      fd(SPEED*0.25);
    }
  }
  ao();                     // หยุด
  delay(100);               // คิดซักนิดก่อนไปต่อ
  /////////////////////////////////////////////

  bk(SPEED);            // ถอยหลัง
  delay(BACKWARD_DELAY);
  ao();
}

void FR() {
  delay(500);       // หยุดคิดซักนิดก่อนไปต่อ
  sr(SPEED*0.75);  // หมุนขวาด้วยความเร็ว 60%
  delay(TURN_R_DELAY);// หมุนนานเท่าใด
  ao();             // หยุด
  delay(500);       // หยุดคิดซักนิดก่อนไปต่อ
}

void FL() {
  delay(500);
  sl(SPEED*0.75);
  delay(TURN_L_DELAY);
  ao();
  delay(500);
}

void KICK() {
  bk(SPEED*0.5);
  delay(BACKWARD_DELAY);
  ao();
  FL();     // เลี่ยวซ้าย 90 องศา
  FL();     // เลี่ยวซ้าย 90 องศา (กลับหลังหัน)
  ao(); 
  delay(500);
  bk(SPEED); 
  delay(BACKWARD_DELAY);
  ao(); 
  delay(500);
//  delay(500); servo(1, 100);
//  delay(500); servo(1, 115);
//  delay(500); servo(1, 90);
  delay(1000);
}

void BL(){}
void BR(){}
void KEEP(){}
void RL(){
//  servo(1, 90);
}

void robot_init(){
	 /* drive motor */
	 pinMode(PWMA,OUTPUT); //PWM Pin 1
	 pinMode(PWMB,OUTPUT); //PWM Pin 2
	 pinMode(ADIR,OUTPUT); //Left Motor Pin 1
	 pinMode(BDIR,OUTPUT);  //Right Motor Pin 2
	 digitalWrite(ADIR, LOW);
	 digitalWrite(BDIR, LOW);
	 /* set to initial val */	
	 ao(); // all motors off
   beep();
	
}

#endif
