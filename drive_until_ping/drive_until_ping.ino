#include <Servo.h>

#define FORWARD 2000
#define BACKWARD 1000
#define STOP 1500

Servo rside;
Servo lside;
const int pingPin = 2;

void setup(){
  rside.attach(12);
}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

int ping(){
  long duration, inches, cm;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  inches = microsecondsToInches(duration);
  return inches;
}

void loop(){
  rside.write(FORWARD);

  if((int) ping() < 10){
    rside.writeMicroseconds(STOP);
    delay(5);
  }
}
