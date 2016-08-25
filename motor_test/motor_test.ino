#include <Servo.h>

#define FORWARD 2000
#define BACKWARD 1000
#define STOP 1500

Servo rside;
Servo lside;

void stopToMaxFor(Servo s){
  for(int i=1500; i<=FORWARD; i++) s.write(i);
  s.write(FORWARD);
}

void setup(){
  rside.attach(12);
}

void loop(){
  rside.write(FORWARD);
  lside.write(FORWARD);
  delay(5);

  rside.write(STOP);
  lside.write(STOP);
  delay(10);
}
