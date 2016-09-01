#include <Arduino.h>
#include <Servo.h>

#define FORWARD 2000
#define BACKWARD 1000
#define STOP 1510

Servo rside;
Servo lside;
int turn = 0;
int irSensorPin = 6;
int irLedPin = 4;
int lightR = 0;
int lightL = 1;
const int sideSwitch = 7;
const int frontPing = 2;
const int sidePing = 11;
bool side = true; //left wall false, right wall true
                  //if we start on the left wall, plug pin7 into 5V

void setup(){
  rside.attach(12);
  lside.attach(10);
  pinMode(irSensorPin, INPUT);
  pinMode(irLedPin, OUTPUT);
  pinMode(sideSwitch, INPUT);
  Serial.begin(9600);
  side = digitalRead(sideSwitch);
}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

int irRead(){
  int halfPeriod = 13;
  int cycles = 38;
  int i;
  for (i=0; i <=cycles; i++){
    digitalWrite(irLedPin, HIGH);
    delayMicroseconds(halfPeriod);
    digitalWrite(irLedPin, LOW);
    delayMicroseconds(halfPeriod - 1);     // - 1 to make up for digitaWrite overhead
  }
  return digitalRead(irSensorPin);
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
  rside.writeMicroseconds(STOP);
  lside.writeMicroseconds(STOP);
  returnToWall();
}

void returnToWall(){
  turnLeft();
  rside.writeMicroseconds(FORWARD-300);
  lside.writeMicroseconds(FORWARD-300);
  delay(15);
  long frontDis = ping(frontPing);
  while(frontDis > 6){
    Serial.print("Front is: ");
    Serial.println(frontDis);
    frontDis = ping(frontPing);
  }
  rside.writeMicroseconds(STOP);
  lside.writeMicroseconds(STOP);
  delay(15);
  delay(1000);
  rside.writeMicroseconds(BACKWARD+400);
  lside.writeMicroseconds(FORWARD-400);
  delay(15);
  delay(2050);
  rside.writeMicroseconds(STOP);
  lside.writeMicroseconds(STOP);
  delay(15);
  delay(1000);
}

void lightNav(){
  Serial.println("Light Hit!");
	while(lightR != lightR){
		if(lightL > lightR){
      Serial.println("Turning Left");
	while(lightR != lightR){
		if(lightL > lightR){
			lside.writeMicroseconds(BACKWARD);
			rside.writeMicroseconds(FORWARD);
			delay(15);
			delay(100);
			}
		else{
      Serial.println("Turning ")
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
	}
    delay(15);
    while(true){}
}

void branchRight(){
  backup();
  turnRight();
  rside.writeMicroseconds(FORWARD-300);
  lside.writeMicroseconds(FORWARD-300);
  delay(15);
  while(!irRead()) {}
  rside.writeMicroseconds(STOP);
  lside.writeMicroseconds(STOP);
  delay(15);
  backup();
  turnRight();
  delay(3000);
  rside.writeMicroseconds(FORWARD-300);
  lside.writeMicroseconds(FORWARD-300);
  delay(15);
  delay(3000);
  rside.writeMicroseconds(STOP);
  lside.writeMicroseconds(STOP);
  delay(15);
  while(true) {}
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

  if(irRead()){
    branchRight();
  }

  if(frontDis <= 15){
    navigateRight();
  }

  if(sideDis >= 20 && sideDis < 30){
    returnToWall();
  }

  if(sideDis >= 30){
    delay(1000);
    turnLeft();
    rside.writeMicroseconds(FORWARD-400);
    lside.writeMicroseconds(FORWARD-400);
    delay(15);
    delay(1500);
    turn += 1;
  }

  if(turn == 2){
    lightNav();
  }
}
