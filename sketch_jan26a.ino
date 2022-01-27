#define trackerPinLS 2  // This define arduino pin no 2 as tracker PIN
#define trackerPinRS 3  // Same concept; right sensor

#define LM1 4 // Left motor
#define LM2 5 // Left motor
#define RM1 6 // Right motor
#define RM2 7 // Right motor


void setup()
{
  
  // put your setup code here, to run once:
  pinMode(trackerPinLS, INPUT); // Set pinmode to receive input from line; LEFT sensor
  pinMode(trackerPinRS, INPUT); // Set pinmode to receive input from line; RIGHT sensor
  // Red light = no line

}

void loop()
{
  // put your main code here, to run repeatedly:

  
  if (digitalRead(trackerPinLS) && digitalRead(trackerPinRS)) // Move Foward
  {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(LM2, LOW);
  }
  
  if(!(digitalRead(LS)) && digitalRead(RS))     // Turn right
  {
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
  }
  
  if(digitalRead(LS) && !(digitalRead(RS)))     // turn left
  {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW);
  }
  
  if(!(digitalRead(LS)) && !(digitalRead(RS)))     // stop
  {
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW);
  }

}
