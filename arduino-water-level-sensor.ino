// Water Level Sensor Practice

const int myWaterSensorPin = A0;   
const int blueLED = 10;         
const int redLED = 9;          
const int potentiometerPin = A1;  

int currentWaterLevel = 0;
int desiredLevel = 0;

const int numReadings = 10;
int readings[numReadings];
int readIndex = 0;
int total = 0;

void setup() {
  Serial.begin(9600);
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  
  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
  }
}

void loop() {
  int sensorValue = analogRead(myWaterSensorPin);
  total -= readings[readIndex];
  readings[readIndex] = sensorValue;
  total += sensorValue;
  readIndex = (readIndex + 1) % numReadings;
  
  int averageSensorValue = total / numReadings;
  currentWaterLevel = map(averageSensorValue, 0, 1023, 0, 30);
  
  int potValue = analogRead(potentiometerPin);
  desiredLevel = map(potValue, 0, 1023, 0, 30);
  
  Serial.print("Current Water Level: ");
  Serial.print(currentWaterLevel);
  Serial.print(" mm, Desired Level: ");
  Serial.print(desiredLevel);
  Serial.println(" mm");
  
// pump is high
  if (currentWaterLevel > desiredLevel + 5) {
    digitalWrite(redLED, HIGH);
    digitalWrite(blueLED, LOW);
  } 
// fan is high
else if (currentWaterLevel < desiredLevel - 5) {
    digitalWrite(redLED, LOW);
    digitalWrite(blueLED, HIGH);
  } 
else {
    digitalWrite(redLED, LOW);
    digitalWrite(blueLED, LOW);
  }
  delay(5000); // 5 seconds delay
}
