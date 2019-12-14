// stdrobot.h
#ifndef stdrobot_h
#define stdrobot_h

#include "pin_mapping_xt.h"
#include <ipst.h>

int L1, L2, R1, R2;
#define THESHOLD 580
extern int SPEED;

//void beep(){
//  tone(buzzer, 1500);
//  delay(50);
//  noTone(buzzer);
//}

//void OK(){
//	while(digitalRead(SW_OK))
//		delay(100);
//  beep();
//  beep();
//}

void fd(int speed){
//  //direction
//  digitalWrite(ADIR, LOW);
//  digitalWrite(BDIR, LOW);
//  // speed
//  analogWrite(PWMA, map(speed, 0, 100, 0, 255));
//  analogWrite(PWMB, map(speed*0.6, 0, 100, 0, 255));
  motor(1,speed); 
  motor(2,speed);
}

void sl(int speed){
//  //direction
//  digitalWrite(ADIR, HIGH);
//  digitalWrite(BDIR, LOW);
//  // speed
//  analogWrite(PWMA, map(speed, 0, 100, 0, 255));
//  analogWrite(PWMB, map(speed, 0, 100, 0, 255));
  motor(1,speed);
  motor(2,-speed);
}

void sr(int speed){
//  //direction
//  digitalWrite(ADIR, LOW);
//  digitalWrite(BDIR, HIGH);
//  // speed
//  analogWrite(PWMA, map(speed, 0, 100, 0, 255));
//  analogWrite(PWMB, map(speed, 0, 100, 0, 255));
  motor(1,-speed);
  motor(2,speed);
}

void tl(int speed){
//  //direction
//  digitalWrite(ADIR, HIGH);
//  digitalWrite(BDIR, LOW);
//  // speed
//  analogWrite(PWMA, 0);
//  analogWrite(PWMB, map(speed, 0, 100, 0, 255));
}

void tr(int speed){
  //direction
//  digitalWrite(ADIR, LOW);
//  digitalWrite(BDIR, HIGH);
//  // speed
//  analogWrite(PWMA, map(speed, 0, 100, 0, 255));
//  analogWrite(PWMB, 0);
}

void bk(int speed){
  //direction
//  digitalWrite(ADIR, HIGH);
//  digitalWrite(BDIR, HIGH);
  
  // speed
//  analogWrite(PWMA, map(speed, 0, 100, 0, 255));
//  analogWrite(PWMB, map(speed, 0, 100, 0, 255));
}

//void ao(){
////  analogWrite(PWMA, 0);
////  analogWrite(PWMB, 0);
//  motor(1,0);
//  motor(2,0);
//}

///////////////////////////////////
void read_sensor(){
	int L2_temp = 0; 
	int L1_temp = 0; 
	int R1_temp = 0;
	int R2_temp = 0;
	for(int i=0; i<5; i++){
		L2_temp	+= analogRead(L2_PORT);
		L1_temp += analogRead(L1_PORT);
		R1_temp += analogRead(R1_PORT);
		R2_temp += analogRead(R2_PORT);
	}
	L2 = L2_temp / 5;
	L1 = L1_temp / 5;
	R1 = R1_temp / 5;
	R2 = R2_temp / 5;

//  glcd(1,1,"L2=%d",L2);
//  glcd(2,1,"L1=%d",L1);
//  glcd(3,1,"R1=%d",R1);
//  glcd(4,1,"R2=%d",R2);
}

void follow_line(){
  read_sensor();
  if(L1<THESHOLD)
  {
    motor(1, SPEED*0.6);
    motor(2, SPEED);
  }
  else if(R1<THESHOLD)
  {
    motor(1, SPEED);
    motor(2, SPEED*0.6);
  }
}

void FF(){
	read_sensor();
	while(L2>THESHOLD && R2>THESHOLD)
	{
		follow_line();
	}
  while(L2<THESHOLD || R2<THESHOLD){
    read_sensor();
    fd(SPEED); delay(10);
  }
}

void FR(){
  motor(1,SPEED*0.6);
  motor(2,-SPEED*0.6);
	delay(100);
	read_sensor();
	while(L1>THESHOLD){
		read_sensor();
	}
  //ao();
  //beep(16);
}
void FL(){
	motor(2,SPEED*0.6);
  motor(1,-SPEED*0.6);
	delay(100);
	read_sensor();
	while(R1>THESHOLD){
		read_sensor();
	}
  //uao();
  //beep(16);
}

void BL(){}
void BR(){}
void KEEP(){}
void RL(){}

void robot_init(){
	 /* drive motor */
//	 pinMode(PWMA,OUTPUT); //PWM Pin 1
//	 pinMode(PWMB,OUTPUT); //PWM Pin 2
//	 pinMode(ADIR,OUTPUT); //Left Motor Pin 1
//	 pinMode(BDIR,OUTPUT);  //Right Motor Pin 2
//	 digitalWrite(ADIR, LOW);
//	 digitalWrite(BDIR, LOW);
    motor(1,0);
    motor(2,0);
	 /* set to initial val */	
	 ao(); // all motors off
   beep(19);
	
}

#endif
