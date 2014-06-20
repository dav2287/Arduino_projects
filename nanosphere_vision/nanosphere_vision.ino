int switchPin = 2;
int resultPin = 6;
int bottomLightPin = 7;
int passLightPin = 8;
int failLightPin = 9;
int failLight2Pin = 10;
int triggerPin = 11;
int jobPin = 12;
int running = LOW;
int oldSwitchPinState = LOW;

void setup() {
  // put your setup code here, to run once:
  pinMode(bottomLightPin, OUTPUT);
  pinMode(passLightPin, OUTPUT);
  pinMode(failLightPin, OUTPUT);
  pinMode(failLight2Pin, OUTPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(jobPin, OUTPUT);
  digitalWrite(switchPin, HIGH);
  digitalWrite(jobPin, HIGH);
  clearStatus();
  running = LOW;
}

void loop() {
  // put your main code here, to run repeatedly: 
  int switchPinState = digitalRead(switchPin);
  if (switchPinState == LOW){
    running = HIGH;
    cycle();
    delay(5);
  }
  delay(1); //debounce
}

void cycle() {
  clearStatus();
  digitalWrite(jobPin, HIGH); //set camera to job 1
  delay(500);
  digitalWrite(triggerPin, HIGH); //trigger the camera
  delay(50);
  digitalWrite(triggerPin, LOW); //turn trigger off
  delay(3000); //wait while test runs
  int result1 = digitalRead(resultPin); //read result from camera
  delay(50);
  digitalWrite(jobPin, LOW); //set camera to job 2
  delay(500);
  digitalWrite(bottomLightPin, HIGH); //turn on bototm light
  delay(50);
  digitalWrite(triggerPin, HIGH); //trigger the camera
  delay(50);
  digitalWrite(triggerPin, LOW); //turn trigger off
  delay(3000); //wait while test runs
  int result2 = digitalRead(resultPin); //read result from camera
  delay(50);
  if (result1 == HIGH && result2 == HIGH){
    digitalWrite(passLightPin, HIGH);
  }
  if (result1 == LOW){
    digitalWrite(failLightPin, HIGH);
  }
  if (result2 == LOW){
    digitalWrite(failLight2Pin, HIGH);
  }
  digitalWrite(triggerPin, LOW);
  digitalWrite(bottomLightPin, LOW);
  digitalWrite(jobPin, HIGH);
  running = LOW; 
}

void clearStatus() {
  digitalWrite(bottomLightPin, LOW);
  digitalWrite(passLightPin, LOW);
  digitalWrite(failLightPin, LOW);
  digitalWrite(failLight2Pin, LOW);
  digitalWrite(triggerPin, LOW);
  digitalWrite(jobPin, HIGH);
}


