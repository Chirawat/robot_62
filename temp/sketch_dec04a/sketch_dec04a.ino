#include <popx2.h>	// POP-X2 Board
#define FrontL (analog(1)>300)
#define FrontR (analog(3)>300)
#define L (analog(0)>300)
#define R (analog(2)>300)
int SPEED = 25;
void FF(){
  fd(SPEED);
  /////////////////////////////////////
  while(FrontL && FrontR){
    if(!L){
      sr(SPEED); delay(100);
    }
    else if(!R){
      sl(SPEED); delay(100);
    }
    else{
      fd(SPEED);
    }
  }

  /////////////////////////////////////
  while(L || R){
    if(!L){
      tl(SPEED);
    }
    if(!R){
      tr(SPEED);
    }
  }
  ao(); delay(500);
  ////////////////////////////////////
  bk(SPEED); delay(350);
  ao();
} 

void FR(){
  sr(SPEED); delay(1200);
  ao();
}

void FL(){
  sl(SPEED); delay(1200);
  ao();
}
void setup() {
  OK();
  FF();
  FR();
  FF();
  FR();
  FF();
  FR();
  FF();
  FL();
  FF();
}

void loop() {

}
