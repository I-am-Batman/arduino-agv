#include <Arduino.h>

#include <Servo.h>

#define FORWARD 1000
#define BACKWARD 2000
#define STOP 1500

Servo rside;
Servo lside;
const int pingPin = 2;

void setup(){
  rside.attach(12);
  Serial.begin(9600);
}


void loop(){
  rside.writeMicroseconds(FORWARD);
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
  Serial.print("in, ");
  Serial.println();

  delay(100);

  if(inches <= 10){
    rside.writeMicroseconds(STOP);
    delay(15);
    delay(5000);
  }

}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}
