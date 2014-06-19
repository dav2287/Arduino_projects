int sensor[] = {A0, A1, A2, A3};
int sensorValue[] = {0, 0, 0, 0};
String readString;
int running = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  while (Serial.available()) {
    delay(10);  
    if (Serial.available() >0) {
      char c = Serial.read();
      readString += c;
    }
  }
  if (readString.length() >0) {
    if (readString == "start") {
      running = 1;
    }
    else if (readString == "stop") {
      running = 0; 
    }
  }
  readString="";
  if (running == HIGH) {
    runtest();
  }
} 

void runtest() {
  for (int i = 0; i < 4; i++) {
    sensorValue[i] = analogRead(sensor[i]);
    delay(5);
    sensorValue[i] = analogRead(sensor[i]);
    delay(5);
  }
  for (int i = 0; i < 3; i++) {
    Serial.print(sensorValue[i]);
    Serial.print("\t");
  }
  Serial.println(sensorValue[3]);
  delay(200);
}
  
