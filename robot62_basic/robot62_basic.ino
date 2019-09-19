#include <popx2.h>

#define SPEED       30            // ความเร็ว
#define WALL_DELAY  160       // มุมเลี้ยวชนผนัง
#define STRAING_DELAY 50
#define BACKWARD_DELAY 500
//#define in(port) readSensor(port)
int TURN_DELAY = 400;
float ANGLE = 0;

int readSensor(int port){
  int val=analog(port);
  return val>200 ? 1:0;
}

void FF() {
  /////////// เช็คผนัง /////////////
  while (readSensor(2)) {          
    if (!readSensor(0)) {
      tr(25);delay(WALL_DELAY);
      ao(); delay(100);
    }
    if (!readSensor(1)) {
      tl(25);delay(WALL_DELAY);
      ao(); delay(100);
    }
    if( readSensor(0) && readSensor(1)) {
      fd(SPEED);
    }
  }
  //ao();while(1);
  //////////// เช็คแยกแล้วตั้งลำ ///////////////
  ao(); delay(100);
  bk(20); delay(600);
  int a0=0;
  int a1=0;
  while (!a0 || !a1) {
    if (!readSensor(0)) {
      tl(SPEED);
      a0 = 1;
    }
    if (!readSensor(1)) {
      tr(SPEED);
      a1 = 1;
    }
    if (readSensor(0) && readSensor(1)){
      fd(SPEED*0.5);
    }
  }
  ao();                     // หยุด
  delay(500);               // คิดซักนิดก่อนไปต่อ
  //while(1);
  /////////////////////////////////////////////

  bk(SPEED);            // ถอยหลัง
  delay(BACKWARD_DELAY);
  ao();
}

void FL() {
  delay(500);
  sl(SPEED);
  delay(TURN_DELAY);
  ao();
  delay(500);
  bk(SPEED);
  while(readSensor(3)){
  }
  int a0=0;
  int a1=0;
  while (!a0 || !a1) {
    if (!readSensor(0)) {
      bk2(0,SPEED);
      a0 = 1;
    }
    if (!readSensor(1)) {
      bk2(SPEED,0);
      a1 = 1;
    }
    if (readSensor(0) && readSensor(1)){
      bk(SPEED*0.5);
    }
  }
  ao(); delay(500);
  fd(SPEED);
  delay(300);ao();
}

void FR() {
  delay(500);
  sr(SPEED);
  delay(TURN_DELAY);
  ao();
  delay(500);
  bk(SPEED);
  while(readSensor(3)){
  }
  int a0=0;
  int a1=0;
  while (!a0 || !a1) {
    if (!readSensor(0)) {
      bk2(0,SPEED);
      a0 = 1;
    }
    if (!readSensor(1)) {
      bk2(SPEED,0);
      a1 = 1;
    }
    if (readSensor(0) && readSensor(1)){
      bk(SPEED*0.5);
    }
  }
  ao(); delay(500);
  fd(SPEED);
  delay(300);ao();
  //while(1);
}


void KICK() {
  bk(10);
  delay(BACKWARD_DELAY);
  ao();
  FL2();     // เลี่ยวซ้าย 90 องศา
  FL();     // เลี่ยวซ้าย 90 องศา (กลับหลังหัน)
  ao(); 
  delay(500);
  bk(20); 
  delay(BACKWARD_DELAY);
  ao(); 
  delay(500);
  delay(500); servo(1, 100);
  delay(500); servo(1, 125);
  delay(500); servo(1, 135);
  delay(500); servo(1, 90);
  delay(1000);
}


void FK() {
  bk(40);

  delay(950);
  ao();
}

void FK2() {
  bk(40);

  delay(1900);
  ao();
}
void FF2() {
  fd(40);

  delay(600);
  ao();
}
void FF3() {
  fd(40);

  delay(1400);
  ao();

}


void FL2() {
  delay(500);
  sl(25);
  delay(TURN_DELAY);
  ao();
  delay(500);
}
void FR2() {
  delay(500);
  sr(25);
  delay(TURN_DELAY);
  ao();
  delay(500);
}

void FL3() {
  delay(500);
  sl(32);
  delay(TURN_DELAY);
  ao();
  delay(500);
}
void FR3() {
  delay(500);
  sr(32);
  delay(TURN_DELAY);
  ao();
  delay(500);
}

void FL4() {
  delay(500);
  sl(22);
  delay(TURN_DELAY);
  ao();
  delay(500);
}
void FR4() {
  delay(500);
  sr(22);
  delay(TURN_DELAY);
  ao();
  delay(500);
}
void setup() {
  servo(1, 90);
  setTextSize(2);
  ///////////////////////////////////

  /* Press OK */
  glcd(0, 0, "Press OK");
  while (!sw_OK()) {
    delay(100);
  }
  glcd(0, 0, "Running ");
  
  ///////////////////////////////////////////////////
  //FF();FR();FF();FR();FF();FR();FF();
  
  //FR();FR();FF();FL();FF();FR();
  FF();FL();FF();FL();FL();
  




  
  glcd(0, 0, "Finished");
}

void loop() {
  //FF();FR();
}
