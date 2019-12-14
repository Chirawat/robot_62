#include <popx2.h>

#define SPEED 50            // ความเร็ว
#define WALL_DELAY 50       // มุมเลี้ยวชนผนัง

#define STRAING_DELAY 10
#define BACKWARD_DELAY 600
int TURN_DELAY = 650;
float ANGLE = 0;

void FF() {
  /////////// เช็คผนัง /////////////
  while (in(26)) {          
    if (!in(24)) {

//      bk(SPEED); delay(100);
      tr(SPEED);delay(WALL_DELAY);
      ao(); delay(100);
    }
    if (!in(25)) {
//      ao(); delay(100);
//      bk(SPEED); delay(100);
      tl(SPEED);delay(WALL_DELAY);
      ao(); delay(100);
    }
    if( in(24) && in(25)) {
      fd(SPEED);
    }
  }
  //ao();while(1);
  //////////// เช็คแยกแล้วตั้งลำ ///////////////
  ao(); delay(100);
  bk(SPEED*0.75); delay(250);
  int a0=0;
  int a1=0;
  while (!a0 || !a1) {
    if (!in(24)) {
      tl(SPEED);
      a0 = 1;
    }
    if (!in(25)) {
      tr(SPEED);
      a1 = 1;
    }
    if (in(24) && in(25)){
      fd(SPEED*0.3);
    }
  }
  //delay(STRAING_DELAY);     // เผื่อหุ่นไม่ตรง เลี้ยวจนตรง 
  ao();                     // หยุด
  delay(500);               // คิดซักนิดก่อนไปต่อ
  //while(1);
  /////////////////////////////////////////////

  bk(SPEED*0.5);            // ถอยหลัง
  delay(BACKWARD_DELAY);
  ao();
}

void FR() {
  delay(500);       // หยุดคิดซักนิดก่อนไปต่อ
  sr(SPEED * 0.5);  // หมุนขวาด้วยความเร็ว 60%
  delay(TURN_DELAY);// หมุนนานเท่าใด
  ao();             // หยุด
  delay(500);       // หยุดคิดซักนิดก่อนไปต่อ
}

void FL() {
  delay(500);
  sl(SPEED * 0.5);
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
  delay(500); servo(1, 100);
  delay(500); servo(1, 115);
  delay(500); servo(1, 90);
  delay(1000);
}


void FF3() {
  fd(SPEED);

  delay(2200);
  ao();
}
void FF2() {
  fd(SPEED);

  delay(500);
  ao();

}
void setup() {
  servo(1, 90);
  setTextSize(2);
  ///////////////////////////////////

  /* Press OK */
  glcd(0, 0, "Press OK");
  while (!sw_OK()) {
//    TURN_DELAY = map(knob(), 0, 1024, 300, 800);
//    glcd(1, 0, "T=%d", TURN_DELAY);
    delay(100);
  }
  glcd(0, 0, "Running ");
  ///////////////////////////////////////////////////
  
  FF();FR();
  FF();FR();
  FF();FR();
  FF();FL();
  FF();
//  BK1();
//  FL();
//  FF2(); 
//  FF();
//  FL();FF();
//  BK1();FR();FF();
//  FL();
//  FF();
//  FR();FF();
//  FR();FF();


  glcd(0, 0, "Finished");
}

void loop() {
  //FF();FR();
}
