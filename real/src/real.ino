#include <Arduino.h>

#include <Servo.h>

#define FORWARD 2000
#define BACKWARD 1000
#define STOP 1501

Servo rside;
Servo lside;
const int sideSwitch = 7;
const int pingPin = 2;
bool side = true; //left wall false, right wall true
                  //if we start on the left wall, plug pin7 into 5V

void setup(){
  rside.attach(12);
  lside.attach(10);
  pinMode(sideSwitch, INPUT);
  Serial.begin(9600);
  side = digitalRead(sideSwitch);
}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

void backup(){
  rside.writeMicroseconds(STOP);
  lside.writeMicroseconds(STOP);
  delay(15);
  delay(1000);
  rside.writeMicroseconds(BACKWARD+300);
  lside.writeMicroseconds(BACKWARD+300);
  delay(15);
  delay(1000);
  rside.writeMicroseconds(STOP);
  lside.writeMicroseconds(STOP);
  delay(15);
  delay(1000);
}

void turnRight(){
  rside.writeMicroseconds(STOP);
  lside.writeMicroseconds(STOP);
  delay(15);
  delay(1000);
  rside.writeMicroseconds(BACKWARD+400);
  lside.writeMicroseconds(FORWARD-400);
  delay(15);
  delay(2025);
  rside.writeMicroseconds(STOP);
  lside.writeMicroseconds(STOP);
  delay(15);
  delay(1000);
}

void turnLeft(){
  rside.writeMicroseconds(STOP);
  lside.writeMicroseconds(STOP);
  delay(15);
  delay(1000);
  lside.writeMicroseconds(BACKWARD+400);
  rside.writeMicroseconds(FORWARD-400);
  delay(15);
  delay(1900);
  rside.writeMicroseconds(STOP);
  lside.writeMicroseconds(STOP);
  delay(15);
  delay(1000);
}

void lUTurn(){
  rside.writeMicroseconds(STOP);
  lside.writeMicroseconds(STOP);
  delay(15);
  delay(1000);
  lside.writeMicroseconds(BACKWARD+400);
  rside.writeMicroseconds(FORWARD-400);
  delay(15);
  delay(4000);
  rside.writeMicroseconds(STOP);
  lside.writeMicroseconds(STOP);
  delay(15);
  delay(1000);
}

void rUTurn(){
  rside.writeMicroseconds(STOP);
  lside.writeMicroseconds(STOP);
  delay(15);
  delay(1000);
  rside.writeMicroseconds(BACKWARD+400);
  lside.writeMicroseconds(FORWARD-400);
  delay(15);
  delay(4000);
  rside.writeMicroseconds(STOP);
  lside.writeMicroseconds(STOP);
  delay(15);
  delay(1000);
}

void loop(){
  rside.writeMicroseconds(FORWARD-300);
  lside.writeMicroseconds(FORWARD-300);
  delay(15);

  long duration, inches;

  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  inches = microsecondsToInches(duration);

  Serial.print(inches);
  Serial.print("in");
  Serial.println();

  delay(100);

  if(inches <= 15){
    turnRight();
    rside.writeMicroseconds(FORWARD-300);
    lside.writeMicroseconds(FORWARD-300);
    delay(15);
    delay(1000);
    turnLeft();
    rside.writeMicroseconds(FORWARD-300);
    lside.writeMicroseconds(FORWARD-300);
    delay(15);
    delay(3000);
    turnLeft();
    rside.writeMicroseconds(FORWARD-300);
    lside.writeMicroseconds(FORWARD-300);
    delay(15);
    delay(1000);
    turnRight();
  }
}
