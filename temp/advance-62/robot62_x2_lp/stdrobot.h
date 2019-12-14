// stdrobot.h
#ifndef stdrobot_h
#define stdrobot_h

#include "pin_mapping_xt.h"
//#include <Servo.h>


int SPEED=30;
#define WALL_DELAY 100       // มุมเลี้ยวชนผนัง

#define STRAING_DELAY 10
#define BACKWARD_DELAY 600

#define in(port) readSensor(port)

int TURN_DELAY = 1700;

int L1, L2, R1, R2;
extern int SPEED;

int readSensor(int port){
  int val=analogRead(port);
  //return val>250 ? 1:0;
  return val;
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
  while (digitalRead(A1)) {          
    if (!in(A0)) {
      sr(SPEED);
      delay(WALL_DELAY);
    }
    else if (!in(A2)) {
      sl(SPEED);
      delay(WALL_DELAY);
    }
    else {
      fd(SPEED);
    }
  }
  beep();beep();
  //ao();while(1);
  //////////// เช็คแยกแล้วตั้งลำ ///////////////
  fd(SPEED);
  while (in(A0) || in(A2)) {
    if (!in(A0)) {
      sl(SPEED);
    }
    else if (!in(A2)) {
      sr(SPEED);
    }
    else{
      fd(SPEED);
    }
  }
  delay(STRAING_DELAY);     // เผื่อหุ่นไม่ตรง เลี้ยวจนตรง 
  ao();                     // หยุด
  delay(500);               // คิดซักนิดก่อนไปต่อ
  /////////////////////////////////////////////

  bk(SPEED);            // ถอยหลัง
  delay(BACKWARD_DELAY);
  ao();
}

void FR() {
  delay(500);       // หยุดคิดซักนิดก่อนไปต่อ
  sr(SPEED);  // หมุนขวาด้วยความเร็ว 60%
  delay(TURN_DELAY);// หมุนนานเท่าใด
  ao();             // หยุด
  delay(500);       // หยุดคิดซักนิดก่อนไปต่อ
}

void FL() {
  delay(500);
  sl(SPEED);
  delay(TURN_DELAY);
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
