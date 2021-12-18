#include <PIDLoop.h>
#include <Pixy2CCC.h>
//#include <Pixy2I2C>
#include <Pixy2Line.h>
#include <Pixy2SPI_SS.h>
//#include <Pixy2UART.h>
#include <Pixy2Video.h>
#include <TPixy2.h>
#include <ZumoBuzzer.h>
#include <ZumoMotors.h>
#include <Wire.h>
//#include <Adafruit_PWMServoDriver.h>

#include <SPI.h>
#include <Pixy2.h>
Pixy2 pixy;

//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define FREQUENCY = 50;

// #include <iostream>
// Libraries
#include <stdlib.h>

using namespace std;

float deadZone = 0.15;
//int baseSpeed = 130;

////////////////////////////////////////////////////////

int cont = 0;
int signature, x, y, width, height;
float cx, cy, area;

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

  Serial.begin(9600);
  Serial.print("Starting...\n");
  pixy.init();
  
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
  float turn = pixyCheck();
  
  if (turn > -deadZone && turn < deadZone) {
    turn = 0;
  }
  if (turn < 0) {
    wheels.right(1);
  }
  else if (turn > 0) {
    wheels.left(1);
  }
  else {
    wheels.foward(2);
  }
  delay(1);
    wheels.foward(2);
    wheels.stopBot(1);
    wheels.left(3);
    wheels.stopBot(1);
    wheels.right(3);
    wheels.stopBot(1);
    running = false;  // Breaks out repeating loop
  }
  
}

float pixyCheck() {
  static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32];
  // grab blocks!
  blocks = pixy.ccc.getBlocks();

  // If there are detect blocks, print them!
  if (blocks)
  {
    signature = pixy.ccc.blocks[0].m_signature;
    height = pixy.ccc.blocks[0].m_height;
    width = pixy.ccc.blocks[0].m_width;
    x = pixy.ccc.blocks[0].m_x;
    y = pixy.ccc.blocks[0].m_y;
    cx = (x + (width / 2));
    cy = (y + (height / 2));
    cx = mapfloat(cx, 0, 320, -1, 1);
    cy = mapfloat(cy, 0, 200, 1, -1);
    area = width * height;

    //        Serial.print("sig: ");
    //        Serial.print(signature);
    //        Serial.print(" x:");
    //        Serial.print(x);
    //        Serial.print(" y:");
    //        Serial.print(y);
    //        Serial.print(" width: ");
    //        Serial.print(width);
    //        Serial.print(" height: ");
    //        Serial.print(height);
    //        Serial.print(" cx: ");
    //        Serial.print(cx);
    //        Serial.print(" cy: ");
    //        Serial.println(cy);

  }
  else {
    cont += 1;
    if (cont == 100) {
      cont = 0;
      cx = 0;
    }
  }
  return cx;
}

float mapfloat(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}
