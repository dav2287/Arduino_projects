#include <Servo.h>
int servoPin = 8;
int buttonPin = 13;
int sensor1 = 12; //cup catch
int sensor2 = 11; //slide right
int noid1 = 7; //slide
int noid2 = 6; //escape
int noid3 = 5; //grip
int noid4 = 4; //flip
int noid5 = 3; //pinch and cup
int noid6 = 9; //push
int sensor1State = 0;
int sensor2State = 0;
int sensor3State = 0;
int sensor4State = 0;
int sensor5State = 0;

Servo servo; //Name the servo

int runNumber = 0; //initialize run number
int buttonState = 0; //initialize button state
int tubeState = 0; //initialize tubeState (start at "closed")
int tubeCount = 0; //initialize tube counter
int ticks = 0; //encoder ticks
int state = 0; //arbitrary state
int target = 0;
float targetf = 0;
float degf = 0;

void setup()
{
  pinMode(noid1, OUTPUT);
  pinMode(noid2, OUTPUT);
  pinMode(noid3, OUTPUT);
  pinMode(noid4, OUTPUT);
  pinMode(noid5, OUTPUT);
  pinMode(noid6, OUTPUT);
  pinMode(buttonPin, INPUT); 
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  digitalWrite(sensor1, HIGH); //turn on pullup resistor
  digitalWrite(sensor2, HIGH);


  servo.attach(servoPin);
  Serial.begin(9600);
  servo.write(90); //tells servo to "home" aka stop.
  attachInterrupt(0, encoderCount, RISING); //set up interrupt for encoder counter on pin 2 (INT0)
}

void toggleValve(int noid, int time){ //Opens specified solenoid for specified amount of time
  digitalWrite(noid, HIGH);
  delay (time);
  digitalWrite(noid, LOW);
}

void switchValve(int noid){
  state = digitalRead(noid);
  if (state == HIGH){
    digitalWrite(noid, LOW);
  }
  else{
    digitalWrite(noid, HIGH);
  }
}

void servoSpin(int target){
  ticks = 0;
  //  degf = (float) deg;
  //  targetf = degf/360;
  //  targetf = targetf*200;
  //  target = (int) targetf;
  Serial.println(target);
  if (target > 0){
    while (ticks < target-5){
      servo.write(45);
    }
    while (ticks < target){
      servo.write(89);
    }
  }
  if (target < 0){
    target = target*(-1);
    while (ticks < target-4){
      servo.write(135);
    }
    while (ticks < target){
      servo.write(91);
    }
  }
  servo.write(90);
}

void escapeCycle(int runs){
  for(int i=0; i<runs; i++){
    digitalWrite(noid5, HIGH); //cup up
    digitalWrite(noid3, HIGH); //open grip
    delay(300);
    toggleValve(noid2, 750); //escapement
    delay(2000);
    //toggleValve(noid6, 300); //push down
    //delay(500);
    switchValve(noid3); //close grip
    delay(300);
    switchValve(noid5); //drop cup and open jaws
    delay(50);
    toggleValve(noid6, 300); //push out
  }
}

void program(int runs){
  for(int i=0; i<runs; i++){
    digitalWrite(noid5, HIGH); //cup up
    digitalWrite(noid3, HIGH); //open grip
    delay(300);
    toggleValve(noid2, 750); //escapement
    delay(1750);
    switchValve(noid3); //close quick
    delay(100);
    switchValve(noid3); //open quick
    delay(100);
    switchValve(noid3); //close quick
    delay(100);
    switchValve(noid3); //open
    delay(450);
    switchValve(noid6); //push down
    delay(500);
    switchValve(noid3); //close grip
    delay(300);
    switchValve(noid5); //drop cup and open jaws
    delay(500);
    switchValve(noid6); //retract push down actuator
    buttonState = digitalRead(buttonPin);
    
    //Wait for button press to move to next step
    while (buttonState == HIGH){ 
      buttonState = digitalRead(buttonPin);
      delay(100);
    }
    
    switchValve(noid1); //slide right
    delay(1500);
    switchValve(noid5); //grip
    delay(500);
    servoSpin(205); //uncap
    delay(300);
    toggleValve(noid4, 3000); //flip open
    delay(300);
    servoSpin(-210); //recap (extra)
    delay(200);
    switchValve(noid5); //ungrip
    delay(500);
    servoSpin(5); //back to "home"
    delay(300);
    switchValve(noid1); //slide left
    delay(1500);
    switchValve(noid5); //cup up
    delay(500);
    switchValve(noid3); //drop
    delay(500);
    switchValve(noid5); //present completed tube
    delay(50);
    toggleValve(noid6, 300); //push out
  }
}

void cycleEscape(int runs){
  digitalWrite(noid3, HIGH); //open grip
  for(int i=0;i<runs;i++){
    toggleValve(noid2,750);
    delay(200);
    tubeCount = tubeCount + 1;
    Serial.println(tubeCount);
  }
}

void loop(){
  servo.write(90);
  sensor1State = digitalRead(sensor1);
  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW){
    program(1);
  }
  delay(200);
}

void encoderCount(){
  ticks++;
  Serial.println(ticks);
}

