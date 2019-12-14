#include <popx2.h>

#define SPEED 50            // ความเร็ว
#define WALL_DELAY 10       // มุมเลี้ยวชนผนัง

#define STRAING_DELAY 10
#define BACKWARD_DELAY 600
int TURN_DELAY = 350;
float ANGLE = 0;

void FF() {
  /////////// เช็คผนัง /////////////
  while (in(26)) {          
    if (!in(24)) {
      tr(SPEED*0.5);
      delay(WALL_DELAY);
    }
    else if (!in(25)) {
      tl(SPEED*0.5);
      delay(WALL_DELAY);
    }
    else {
      fd(SPEED);
    }
  }
  //ao();while(1);
  //////////// เช็คแยกแล้วตั้งลำ ///////////////
  fd(SPEED*0.5);
  while (in(24) || in(25)) {
    if (!in(24)) {
      tl(SPEED);
    }
    else if (!in(25)) {
      tr(SPEED);
    }
    else{
      fd(SPEED);
    }
  }
  delay(STRAING_DELAY);     // เผื่อหุ่นไม่ตรง เลี้ยวจนตรง 
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
    TURN_DELAY = map(knob(), 0, 1024, 300, 800);
    glcd(1, 0, "T=%d", TURN_DELAY);
    delay(100);
  }
  glcd(0, 0, "Running ");
  ///////////////////////////////////////////////////

  FF(); FL();
  FF();

  glcd(0, 0, "Finished");
}

void loop() {
  //FF();FR();
}
