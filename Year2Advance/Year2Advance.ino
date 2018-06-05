// Initialize pins
const int lineLeft = 1, lineRight = 1, lineBack = 1;
const int echoLeft = 1, echoMiddle = 1, echoRight = 1;
const int trigLeft = 1, trigMiddle = 1, trigRight = 1;
const int motorLeft = 1, motorRight = 1, button = 2;

int white, safety = 100;
byte  lineState = 0, ultraState = 0;

boolean turnRight = true, sumoStart = false;

// motor speed
int foward = 1300, brake = 1500, backward = 1700;

// library
#include<Servo.h>

void setup() {
  // put your setup code here, to run once:
  pinMode(echoLeft, INPUT); pinMode(echoMiddle, INPUT); pinMode(echoRight, INPUT);
  pinMode(trigLeft, OUTPUT); pinMode(trigMiddle, OUTPUT); pinMode(trigRight, OUTPUT); 

  pinMode(lineLeft, INPUT); pinMode(lineRight, INPUT); pinMode(lineBack, INPUT);
  pinMode(button, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  // start sumobot
  if (sumoStart){

    // read linesensor
    lineState = 0;
    if (safe(lineBack)) lineState += B100;
    if (safe(lineRight)) lineState += B010;
    if (safe(lineLeft)) lineState += B001;
  
    switch (lineState){
  
      // line sensor is safe
      case B000:

        // detect robot
        if (checkDistance(trigMiddle, echoMiddle)){
          setMotor(motorLeft, foward);
          setMotor(motorRight, foward);

        // sonar
        } else {
          if (turnRight){
            setMotor(motorLeft, foward);
            setMotor(motorRight, backward);
          } else {
            setMotor(motorRight, foward);
            setMotor(motorLeft, backward);
          }
        }

        
        
      break;
  
      // left linesensor
      case B001:
        turnRight = true;
        setMotor(motorLeft, foward);
        setMotor(motorRight, backward);
      break;
  
      // right linesensor
      case B010:
        setMotor(motorRight, foward);
        setMotor(motorLeft, backward);
      break;
  
      // left right linesensor
      case B011:
        setMotor(motorLeft, backward);
        setMotor(motorRight, backward);
      break;
  
      // back linesensor
      case B100:
        setMotor(motorLeft, foward);
        setMotor(motorRight, foward);
      break;
  
      // back left linsensor
      case B101:
        setMotor(motorLeft, foward);
        setMotor(motorRight, brake);
      break;
  
      // back right linesensor
      case B110:
        setMotor(motorRight, foward);
        setMotor(motorLeft, brake);
      break;
  
      // back left right linesensor
      case B111:
        setMotor(motorLeft, backward);
        setMotor(motorRight, backward);
      break;
    }
  } else {
    // button pressed to start
    if (digitalRead(button) == HIGH){
      while (digitalRead(button) == HIGH){
      }
      calibrate();
      delay(5200); // delay 5.2 seconds
      sumoStart = true;
    }
  }

}

// set motor speed
void setMotor(int motor, int Direction){
  
}


// method to check distance
boolean checkDistance(int trigger, int echo){
  int duration;

  // send signal
  delayMicroseconds(2); // delay to prevent ultrasensor overheat
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  // read signal
  duration = pulseIn(echo, HIGH, 5800);
  return duration > 58;
  
  //duration /= 58; // convert seconds to distance: uS/58 = cm
  //return duration;
}

// calibrate lighting
void calibrate(){
  white = analogRead(lineBack);
}

boolean safe(int linesensor){
  return analogRead(linesensor) < white + safety; // white value is 20
}


