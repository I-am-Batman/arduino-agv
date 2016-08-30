#include <Arduino.h>

#include <Servo.h>

#define FORWARD 2000
#define BACKWARD 1000
#define STOP 1500

Servo rside;
Servo lside;


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
