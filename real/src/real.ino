#include <Arduino.h>

#include <Servo.h>

#define FORWARD 1000
#define BACKWARD 2000
#define STOP 1500

Servo rside;
Servo lside;
int sideSwitch = 7;
bool side = true; //left wall true, right wall false
                  //if we start on the left wall, plug pin7 into 5V


void setup(){
  rside.attach(12);
  lside.attach(10);
  pinMode(sideSwitch, INPUT);
  Serial.begin(9600);
  side = digitalRead(sideSwitch);
}

void loop(){

}
