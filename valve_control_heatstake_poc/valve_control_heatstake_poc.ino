#include <Servo.h>

/*

This is a program to turn on and off solenoid valves.
It requires NPN transistors connected to the output pins, 
and the transistors are used for low-side switching of the solenoids.

Transistor product page: http://www.fairchildsemi.com/ds/2N/2N3904.pdf
Base pin connected to 1k resistor to output pin of Arduino,
Collector pin connected to ground pin of solenoid valve,
Emitter pin connected to Arduino Gnd.

Positive side of solenoid valve connected to power (likely 24V).
Power supply GND must be connected to Arduino GND.

*/

int noid1 = 8;
int noid2 = 7;
int noid3 = 6;
int noid4 = 5;
int noid5 = 4;
int buttonPin = 3;

boolean buttonState; //initialize button state

void setup()
{
  pinMode(noid1, OUTPUT);
  pinMode(noid2, OUTPUT);
  pinMode(noid3, OUTPUT);
  pinMode(noid4, OUTPUT);
  pinMode(noid5, OUTPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH); //Turn on pull-up resistor.
}

void cycle(int runs){
  for(int i=0; i<runs; i++){
    digitalWrite(noid2, HIGH); //raise bottom
    delay(1000); //Delay before the top comes down
    digitalWrite(noid1, HIGH); //lower top
    delay(3000); //Clamp time pre-blow
    digitalWrite(noid1, LOW); //lift top
    delay(500);
    digitalWrite(noid3, HIGH); //blower on
    delay(2000); //cooling
    digitalWrite(noid3, LOW); //blower off
    digitalWrite(noid2, LOW); //lower bottom
    delay(500);
  }
}

void loop()
{
  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW) cycle(1);
  delay(10);
}
