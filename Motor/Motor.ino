int leftForward = 6, leftBackward = 9, rightForward = 10, rightBackward = 11;

void initMotor(){
  pinMode(leftForward, OUTPUT);
  pinMode(leftBackward, OUTPUT);
  pinMode(rightForward, OUTPUT);
  pinMode(rightBackward, OUTPUT);
}

void setup() {
  // put your setup code here, to run once:
  initMotor();
  digitalWrite(rightForward, HIGH);
  digitalWrite(rightBackward, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

}
