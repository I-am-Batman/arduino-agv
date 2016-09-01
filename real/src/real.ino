#include <Arduino.h>
#include <Servo.h>

#define FORWARD 2000
#define BACKWARD 1000
#define STOP 1510

Servo rside;
Servo lside;
int turn = 0;
const int sideSwitch = 7;
const int frontPing = 2;
const int sidePing = 11;
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
  delay(2250);
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

long ping(int pingPin){
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
  return inches;
}

void navigateRight(){
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

void returnToWall(){
  turnLeft();
  rside.writeMicroseconds(FORWARD-300);
  lside.writeMicroseconds(FORWARD-300);
  delay(15);
  while(ping(frontPing) > 6) {}
  rside.writeMicroseconds(STOP);
  lside.writeMicroseconds(STOP);
  delay(15);
  rside.writeMicroseconds(STOP);
  lside.writeMicroseconds(STOP);
  delay(15);
  delay(1000);
  rside.writeMicroseconds(BACKWARD+400);
  lside.writeMicroseconds(FORWARD-400);
  delay(15);
  delay(1900);
  rside.writeMicroseconds(STOP);
  lside.writeMicroseconds(STOP);
  delay(15);
  delay(1000);
}

void lightNav(){
	while(lightR != lightR){
		if(lightL > lightR){
			lside.writeMicroseconds(BACKWARD);
			rside.writeMicroseconds(FORWARD);
			delay(15);
			delay(100);
			}
		else{
			lside.writeMicroseconds(FORWARD);
			rside.writeMicroseconds(BACKWARD);
			delay(15);
			delay(100);
			}
		delay(15);
		rside.writeMicroseconds(FORWARD);
		lside.writeMicroseconds(FORWARD);
		delay(15);
		delay(200);
	}
	if(lightL < 70){
		rside.writeMicroseconds(STOP);
		lside.writeMicroseconds(STOP);
		delay(15);
	}      
    delay(15);
    while(true){}
}

void loop(){
  rside.writeMicroseconds(FORWARD-300);
  lside.writeMicroseconds(FORWARD-300);
  delay(15);

  long frontDis = ping(frontPing);
  long sideDis = ping(sidePing);

  Serial.print(frontDis);
  Serial.print("in");
  Serial.println();

  if(frontDis <= 15){
    navigateRight();
    sideDis = ping(sidePing);
  }

  if(sideDis >= 20 && sideDis < 30){
    returnToWall();
  }

  if(sideDis >= 30){
    delay(500);
    turnLeft();
    rside.writeMicroseconds(FORWARD-300);
    lside.writeMicroseconds(FORWARD-300);
    delay(15);
    delay(700);
    turn += 1;
  }

  if(turn == 2){
    lightNav();
  }
}
