// stdrobot.h
#ifndef stdrobot_h
#define stdrobot_h

#include "pin_mapping_xt.h"

int L1, L2, R1, R2;
extern int SPEED;

void OK(){
	while(digitalRead(SW_OK))
		delay(100);
}

void fd(int speed){
  //direction
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
}

void follow_line(){
  read_sensor();
  if(L1<500 && R1<500)
  {
    fd(SPEED);
  }
  else if(L1>500 && R1>500)
  {
    fd(SPEED);
  }
  else if(L1<500)
  {
    tl(SPEED);
    //delay(10);
  }
  else if(R1<500)
  {
    tr(SPEED);
    //delay(10);
  }
}

void FF(){
	read_sensor();
	while(L2>500&&R2>500)
	{
		follow_line();
	}
	delay(100);
	ao();
}

void FR(){
	sr(SPEED); 
	delay(300);
	read_sensor();
	while(R1>500){
		read_sensor();
	}
	ao();
	delay(100);
}
void FL(){
	sl(SPEED); 
	delay(300);
	read_sensor();
	while(L1>500){
		read_sensor();
	}
	ao();
	delay(100);
}

void BL(){}
void BR(){}
void KEEP(){}
void RL(){}

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
	
}

#endif