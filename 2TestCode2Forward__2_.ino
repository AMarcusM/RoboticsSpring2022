/*

*/

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

void setup() {
  // put your setup code here, to run once:
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
  // Variable to simplify speed
  int i = speedControl(5);
  if(running){
      moveFoward(i);
      delay(2000);
      stopMoving();
      turnLeft();
      delay(3000);
      stopMoving();
      turnRight();
      delay(2500);
      stopMoving();
      moveFoward(i);
      delay(1500);
      stopMoving();
      
      running = false;  // Breaks out repeating loop
  }

}

// This function lets you move robot foward
int speedControl(int distance) {
  // For PWM maximum possible values are 0 to 255
  // This is from foward function, we want 5 gears

  int currentSpeed, newDistance;
  const int THIRDGEAR=204, SECONDGEAR=153, FIRSTGEAR=102, FAR=500, MID=300, CLOSE=100;
  
  if(distance <= CLOSE) {  //check or test what does y equal when checking object through camera

    return FIRSTGEAR;    
  }
  
  else if(distance <= MID && distance > CLOSE) {  //check or test what does y equal when checking object through camera

    return SECONDGEAR;

  }
  
  else if(distance <= FAR && distance > MID) {  //check or test what does y equal when checking object through camera

    return THIRDGEAR;

  }
  
  else if(distance > FAR) {  //check or test what does y equal when checking object through camera

    return THIRDGEAR;

  }
    


}

void gradualSpeed(int currentSpeed){
  //this.currentSpeed -= 10;
}

// This function lets you move robot foward
void moveFoward() {
  // For PWM maximum possible values are 0 to 255
  analogWrite(frontLeftEn, 115);
  analogWrite(frontRightEn, 115);
  analogWrite(backLeftEn, 115);
  analogWrite(backRightEn, 115);

  // Turn on motors
  digitalWrite(frontLeftin1, HIGH);
  digitalWrite(frontLeftin2, LOW);
  digitalWrite(frontRightin3, LOW);
  digitalWrite(frontRightin4, HIGH);
  digitalWrite(backLeftin3, LOW);
  digitalWrite(backLeftin4, HIGH);
  digitalWrite(backRightin1, HIGH);
  digitalWrite(backRightin2, LOW);

}

// This function lets you TURN robot RIGHT
void turnRight() {
  analogWrite(frontLeftEn, 135);
  analogWrite(frontRightEn, 135);
  analogWrite(backLeftEn, 135);
  analogWrite(backRightEn, 135);

  // Turn on motors
  digitalWrite(frontLeftin1, HIGH);
  digitalWrite(frontLeftin2, LOW);
  digitalWrite(frontRightin3, LOW);
  digitalWrite(frontRightin4, LOW);
  digitalWrite(backLeftin3, LOW);
  digitalWrite(backLeftin4, HIGH);
  digitalWrite(backRightin1, LOW);
  digitalWrite(backRightin2, LOW);

}

// This function lets you TURN robot LEFT
void turnLeft() {
  analogWrite(frontLeftEn, 135);
  analogWrite(frontRightEn, 135);
  analogWrite(backLeftEn, 135);
  analogWrite(backRightEn, 135);

  // Turn on motors
  digitalWrite(frontLeftin1, LOW);
  digitalWrite(frontLeftin2, LOW);
  digitalWrite(frontRightin3, LOW);
  digitalWrite(frontRightin4, HIGH);
  digitalWrite(backLeftin3, LOW);
  digitalWrite(backLeftin4, LOW);
  digitalWrite(backRightin1, HIGH);
  digitalWrite(backRightin2, LOW);

}

void stopMoving() {
  // Turn off motors
  digitalWrite(frontLeftin1, LOW);
  digitalWrite(frontLeftin2, LOW);
  digitalWrite(frontRightin3, LOW);
  digitalWrite(frontRightin4, LOW);
  digitalWrite(backLeftin3, LOW);
  digitalWrite(backLeftin4, LOW);
  digitalWrite(backRightin1, LOW);
  digitalWrite(backRightin2, LOW);

  delay(1000);
}

/*
additonal code needed for future:
Functions- Reverse(); Constants- CHANGE_IN_SPEED, DISTANCE_FROM_OBJECT;
Remember that:
  Pixymon object tracking is based on color and shape (meaning a ruler,
    marker, paper, and proper measurements should suffice)
  LineTracker is a different function and CANNOT operate at the same time as object tracking

*/
