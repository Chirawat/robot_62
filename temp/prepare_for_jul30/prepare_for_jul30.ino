#include "stdrobot.h"
int SPEED = 50;
void setup() {
  robot_init();
  ////////////////
  OK();  
}

void loop() {

  fd(100); delay(1000);
  bk(100); delay(1000);
  sl(100); delay(1000);
  sr(100); delay(1000);
  tl(100); delay(1000);
  tr(100); delay(1000);
  ao(); delay(1000);
}
