// #include <iostream>
// Libraries
#include <stdlib.h>

using namespace std;

// Create variable to break out loop 
boolean running = true;

// Motor A connections front left motor 
int frontLeftEn = 23;
int frontLeftin1 = 25;
int frontLeftin2 = 27;
// Motor B connections front right motor
int frontRightEn = 53;
int frontRightin3 = 49;
int frontRightin4 = 51;

// Motor C connections back left motor 
int backLeftEn = 13;
int backLeftin3 = 11;
int backLeftin4 = 12;
// Motor D connections back right motor
int backRightEn = 8;
int backRightin1 = 9;
int backRightin2 = 10;

class Move
{

	protected:
	// variables needed for move class
	 int var;
	
	public:
	 Move(){}
	 
	 // This function lets you move robot foward
	 void foward(double var) {
	   // For PWM maximum possible values are 0 to 255
	   analogWrite(frontLeftEn, 115);
	   analogWrite(frontRightEn, 115);
	   analogWrite(backLeftEn, 115);
	   analogWrite(backRightEn, 115);
	   
	   // Turn on motors
	   digitalWrite(frontLeftin1, LOW);
	   digitalWrite(frontLeftin2, HIGH);
	   digitalWrite(frontRightin3, HIGH);
	   digitalWrite(frontRightin4, LOW);
	   digitalWrite(backLeftin3, LOW);
	   digitalWrite(backLeftin4, HIGH);
	   digitalWrite(backRightin1, HIGH);
	   digitalWrite(backRightin2, LOW);
	   
	   delay(var*1000);
	   
	 }
	 
	 // This function lets you TURN robot RIGHT
	 void right(double var) {
	   // For PWM maximum possible values are 0 to 255
	   analogWrite(frontLeftEn, 135);
	   analogWrite(frontRightEn, 135);
	   analogWrite(backLeftEn, 135);
	   analogWrite(backRightEn, 135);
	   
	   // Turn on motors
	   digitalWrite(frontLeftin1, LOW);
	   digitalWrite(frontLeftin2, HIGH);
	   digitalWrite(frontRightin3, LOW);
	   digitalWrite(frontRightin4, LOW);
	   digitalWrite(backLeftin3, LOW);
	   digitalWrite(backLeftin4, HIGH);
	   digitalWrite(backRightin1, LOW);
	   digitalWrite(backRightin2, LOW);
	   
	   delay(var*1000);
	   
	 }
	 
	 // This function lets you TURN robot LEFT
	 void left(double var) {
	   // For PWM maximum possible values are 0 to 255
	   analogWrite(frontLeftEn, 135);
	   analogWrite(frontRightEn, 135);
	   analogWrite(backLeftEn, 135);
	   analogWrite(backRightEn, 135);
	   
	   // Turn on motors
	   digitalWrite(frontLeftin1, LOW);
	   digitalWrite(frontLeftin2, LOW);
	   digitalWrite(frontRightin3, HIGH);
	   digitalWrite(frontRightin4, LOW);
	   digitalWrite(backLeftin3, LOW);
	   digitalWrite(backLeftin4, LOW);
	   digitalWrite(backRightin1, HIGH);
	   digitalWrite(backRightin2, LOW);
	   
	   delay(var*1000);
	   
	 }
	 
	 // This function STOPS robot
	 void stopBot(double var) {

	   // Turn off motors
	   digitalWrite(frontLeftin1, LOW);
	   digitalWrite(frontLeftin2, LOW);
	   digitalWrite(frontRightin3, LOW);
	   digitalWrite(frontRightin4, LOW);
	   digitalWrite(backLeftin3, LOW);
	   digitalWrite(backLeftin4, LOW);
	   digitalWrite(backRightin1, LOW);
	   digitalWrite(backRightin2, LOW);
	   
	   delay(var*1000);
	   
	 }
};

// CLASS VARIABLE DECLARATIONS
Move wheels = Move();

void setup() {
  // Set all the motor control pins to outputs
  pinMode(frontLeftEn, OUTPUT);
  pinMode(frontRightEn, OUTPUT);
  pinMode(frontLeftin1, OUTPUT);
  pinMode(frontLeftin2, OUTPUT);
  pinMode(frontRightin3, OUTPUT);
  pinMode(frontRightin4, OUTPUT);

  pinMode(backLeftEn, OUTPUT);
  pinMode(backRightEn, OUTPUT);
  pinMode(backLeftin3, OUTPUT);
  pinMode(backLeftin4, OUTPUT);
  pinMode(backRightin1, OUTPUT);
  pinMode(backRightin2, OUTPUT);

  // Turn off motors - Initial state
  digitalWrite(frontLeftin1, LOW);
  digitalWrite(frontLeftin2, LOW);
  digitalWrite(frontRightin3, LOW);
  digitalWrite(frontRightin4, LOW);
  digitalWrite(backLeftin3, LOW);
  digitalWrite(backLeftin4, LOW);
  digitalWrite(backRightin1, LOW);
  digitalWrite(backRightin2, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(running){
    wheels.foward(2);
    wheels.stopBot(1);
    wheels.left(3);
    wheels.stopBot(1);
    running = false;  // Breaks out repeating loop
  }
  
}
