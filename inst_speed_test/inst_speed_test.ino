unsigned long time;
const int digitalPin = 2;
const int ledPin = 13;
int buttonPushCounter = 0;
int buttonState = 0;
int lastButtonState = 0;
int long prevTime = 0;
int long delta = 0;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // intialize serial comm:
  Serial.begin(19200);
}

void loop() {
  int digitalValue = digitalRead(digitalPin);
  int buttonState = digitalRead(digitalPin);

  if (buttonState != lastButtonState){
    if (buttonState == LOW) {

      digitalWrite(ledPin, HIGH);
      //Serial.print("Time: ");
      time = micros();
      delta = (time - prevTime);
      Serial.println(delta);
    }
    lastButtonState = buttonState;
    prevTime = time;

  }
  else {
    digitalWrite(ledPin, LOW);
  }
}
