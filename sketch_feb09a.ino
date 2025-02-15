#include <PIDLoop.h>
#include <Pixy2.h>
#include <Pixy2CCC.h>
#include <Pixy2I2C.h>
#include <Pixy2Line.h>
#include <Pixy2SPI_SS.h>
#include <Pixy2UART.h>
#include <Pixy2Video.h>
#include <TPixy2.h>
#include <ZumoBuzzer.h>
#include <ZumoMotors.h>

// Camera Pixy
#define I2C
#include <SPI.h>

#ifdef I2C
Pixy2I2C pixy;
#endif

// Servo Driver
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41);
////////////////////////////////////////////////////////

// Black Line Follower 
int IR1=26;    //Right sensor
int IR2=24;    //left Sensor

// ENA IN1 IN2 IN3 IN4 ENB
int myPins [6] = {5, 6, 7, 8, 9, 10};
float deadZone = 0.15;
int baseSpeed = 130;

////////////////////////////////////////////////////////

int cont = 0;
int signature, x, y, width, height;
float cx, cy, area;

void setup() 
{
  // put your setup code here, to run once:
  pinMode(IR1,INPUT);
  pinMode(IR2,INPUT);

  // Wheel & motor pins
  for (int i = 0; i < 6; i++) {
    pinMode(myPins[i], OUTPUT);
  }

  // Start Camera
  Serial.begin(9600);
  Serial.print("Starting...n");
  pixy.init();

  // Arm movement
  pwm1.begin();
  pwm1.setPWMFreq(1600);  // This is the maximum PWM frequency

  pwm2.begin();
  pwm2.setPWMFreq(1600);  // This is the maximum PWM frequency
  
}
void loop() 
{
   if(digitalRead(IR1)==HIGH && digitalRead(IR2)==HIGH) //IR will not glow on black line
  {
    //Stop both Motors
    digitalWrite(myPins[1], 0);
    digitalWrite(myPins[2], 0);
    digitalWrite(myPins[3], 0);
    digitalWrite(myPins[4], 0);
    analogWrite(myPins[0], 0);
    analogWrite(myPins[5], 0);
  }

  else if(digitalRead(IR1)==LOW && digitalRead(IR2)==LOW)  //IR not on black line
  {
    //Move both the Motors
    moveRobot(70, 70);
  }

  else if(digitalRead(IR1)==LOW && digitalRead(IR2)==HIGH)
  {
    //Tilt robot towards left by stopping the left wheel and moving the right one
    moveRobot(-80, 170);
    delay(100);
  }

  else if(digitalRead(IR1)==HIGH && digitalRead(IR2)==LOW)
  {
    //Tilt robot towards right by stopping the right wheel and moving the left one
    moveRobot(170, -80);
    delay(100);
  }

  else
  {
    //Stop both the motors
    digitalWrite(myPins[1], 0);
    digitalWrite(myPins[2], 0);
    digitalWrite(myPins[3], 0);
    digitalWrite(myPins[4], 0);
    analogWrite(myPins[0], 0);
    analogWrite(myPins[5], 0);

  }

  float turn = pixyCheck();
  if (turn > -deadZone && turn < deadZone) {
    turn = 0;
  }
  if (turn < 0) {
    moveRobot(-80, 170);
  }
  else if (turn > 0) {
    moveRobot(170, -80);
  }
  else {
    moveRobot(70, 70);
  }
  
  delay(1);
}

float pixyCheck() {
  static int i = 0;
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

        Serial.print("sig: ");
            Serial.print(signature);
            Serial.print(" x:");
            Serial.print(x);
            Serial.print(" y:");
            Serial.print(y);
            Serial.print(" width: ");
            Serial.print(width);
            Serial.print(" height: ");
            Serial.print(height);
            Serial.print(" cx: ");
            Serial.print(cx);
            Serial.print(" cy: ");
            Serial.println(cy);

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

void moveRobot(int leftSpeed, int rightSpeed)
{
  if (leftSpeed >= 0) {
    digitalWrite(myPins[1], 1);
    digitalWrite(myPins[2], 0);
  }
  else {
    digitalWrite(myPins[1], 0);
    digitalWrite(myPins[2], 1);
  }

  if (rightSpeed >= 0) {
    digitalWrite(myPins[3], 0);
    digitalWrite(myPins[4], 1);
  }
  else {
    digitalWrite(myPins[3], 1);
    digitalWrite(myPins[4], 0);
  }

  analogWrite(myPins[0], abs(leftSpeed));
  analogWrite(myPins[5], abs(rightSpeed));
}
