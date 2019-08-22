#include <ATX2.h>	// POP-X2 Board
int SPEED = 30;

void FF(){
  fd(SPEED);
  while(in(24)==1 || in(25)==1){
    if(in(24)==0)
      sl(30);
    if(in(25)==0)
      sr(30);
  }
    
  bk(SPEED);
  delay(300);
  ao(); 
}

void FR(){
  sr(SPEED);
  delay(320);
  ao();
}

void FL(){
  sl(SPEED);
  delay(320);
  ao();
}



void setup() {
  servo(1, 90);
  OK();
  FF(); 
  delay(1000);
  servo(1,0);
  delay(1000);
  servo(1, 90);
  FL();
  FF();
  delay(1000);
  servo(1,0);
  delay(1000);
  servo(1, 90);
  //FL(); FF();
}

void loop() {
}
