#include <ATX2.h>	
int SPEED = 30;
int AN0 = 0;
int AN1 = 0;
int AN2 = 0;
int AN3 = 0;

void read_sensor(){
  // A0 => 24
  // A1 => 25
  // A2 => 26
  // A3 => 27
  int a0_t = analog(0); 
  int a1_t = analog(1);
  int a2_t = analog(2);
  int a3_t = analog(3);
  if(a0_t>200){
    AN0 = 1;
  }
  else{
    AN0 = 0;
  }
  
  if(a1_t>200){
    AN1 = 1;
  }
  else{
    AN1 = 0;
  }

  if(a2_t>200){
    AN2 = 1;
  }
  else{
    AN2 = 0;
  }

  if(a3_t>200){
    AN3 = 1;
  }
  else{
    AN3 = 0;
  }
}

void FF(){
  fd(SPEED);
  read_sensor();
  while(AN0==1 || AN1==1){
    if(AN0==0)
      sl(15);
    if(AN1==0)
      sr(15);
    read_sensor();
  }
    
  bk(15);
  delay(800);
  ao(); 
}
void FF2(){
  fd(SPEED);
  read_sensor();
  while(AN0==1 || AN1==1){
    if(AN0==0)
      sl(15);
    if(AN1==0)
      sr(15);
  }
    
  bk(15);
  delay(3200);
  ao(); 
}

void FK(){
  bk(SPEED);
  read_sensor();
  while(AN2==1 || AN3==1){
    if(AN2==0)
      sr(15);
    if(AN3==0)
      sl(15);
    read_sensor();
  }
    
  fd(15);
  delay(1500);
  ao(); 
}

void FR(){
  sr(SPEED);
  delay(300);
  ao();
}

void FL(){
  sl(SPEED);
  delay(300);
  ao();
}

void KICK(){
  delay(1000);
  servo(1,0);
  delay(1000);
  servo(1, 90);
  delay(1000);
}


void setup() {
  OK();
  delay(1000);
  FF();FR();
  FF();FR();
  FF();FR();FF();
  FL();FF();
  FF2();
  FL();
  fd(30); delay(1900);ao();
  FR();FF();FR();FF();
  FK();
  FR();FF();FR();FF();
  KICK();
}

void loop() {
}
