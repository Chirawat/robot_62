#include <popx2.h>	// POP-X2 Board
int L, L1, R, R1, x=0;
int dist = 0;
int SPEED = 50;
void read_sensor()
{
  L1  = analog(0);
  L   = analog(1);
  R   = analog(2);
  R1  = analog(3);
}

void follow_line()
{
  read_sensor();
  if(L<500 && R<500)
  {
    fd(SPEED);
  }
  else if(L>500 && R>500)
  {
    fd(SPEED);
  }
  else if(L<500)
  {
    tl(SPEED);
    sleep(20);
  }
  else if(R<500)
  {
    tr(SPEED);
    sleep(20);
  } 
}
void FF()
{
  read_sensor();
  while(L1>500&&R1>500)
  {
    follow_line();
  }
  sleep(35);
  ao();
  sleep(100);
}

void FL()
{
  sl(SPEED); 
  delay(300);
  read_sensor();
  while(L>500){
    read_sensor();
  }
  ao();
  sleep(100);
}
void FR()
{
  sr(SPEED); 
  delay(300);
  read_sensor();
  while(R>500){
    read_sensor();
  }
  ao();
  sleep(100);
}
void down()
{
  servo(1, 60);
  delay(500);
}
void up()
{
  servo(1, 120);
  delay(500);
}
void keep()
{
  while(getdist(4)>10)
  {
    follow_line();
  }
  ao();
  delay(500);
  down();
  delay(500);
  servo(2, 115);
  delay(500);
  up();
  delay(500);
}
void rl()
{
  down();
  delay(500);
  servo(2, 90);
  delay(500);
  up();
  delay(500);
}
void setup() 
{
  up();
  rl();c  Z
  OK();
  ////////////////////////////////
  keep();FF();FR();FF();FR();FF();rl();
  FR(); 
}

void loop() 
{
  
}
