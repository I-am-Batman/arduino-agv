#include <Arduino.h>

#include <Servo.h>

#define FORWARD 1 000
#define BACKWARD 2000
#define STOP 1500

Servo rside;
Servo lside;

void stopToMaxFor(Servo s){
  for(int i=1500; i<=FORWARD; i++) s.writeMicroseconds(i);
  s.writeMicroseconds(FORWARD);
}

void setup(){
  rside.attach(12);
  lside.attach(10);
}

void loop(){
  rside.writeMicroseconds(FORWARD);
  delay(15);
  lside.writeMicroseconds(FORWARD);
  delay(15);
  delay(5000);

  rside.writeMicroseconds(STOP);
  delay(15);
  lside.writeMicroseconds(STOP);
  delay(15);
  delay(3000);
}
