#include <DHT.h>

#define DHTPIN 4   // Digital pin for DHT sensor
#define DHTTYPE DHT11  // DHT sensor type (change to DHT22 if you're using that sensor)

DHT dht(DHTPIN, DHTTYPE);

int trigPin = 9;
int echoPin = 10;
int flamePin = 2;
int gasSensorPin = A0;
int buzzerPin = 7;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(flamePin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  dht.begin();
  Serial.begin(9600);
}

void loop() {
  // Ultrasonic sensor
  long duration, distance;
  duration = readUltrasonicSensor(trigPin, echoPin);
  distance = (duration / 2) / 29.1;  // Calculate distance in centimeters

  int flameDetected = digitalRead(flamePin);
  int gasValue = analogRead(gasSensorPin);

  // Temperature and Humidity sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check for dangerous conditions and activate the buzzer
  if (distance < 50 || flameDetected == LOW || gasValue > 100) {
    activateBuzzer();
  } else {
    deactivateBuzzer();
  }

  // Print sensor values
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm, Flame Detected: ");
  Serial.print(flameDetected);
  Serial.print(", Gas Value: ");
  Serial.print(gasValue);
  Serial.print(", Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  delay(5000);  // Adjust the delay for sensor reading frequency
}

long readUltrasonicSensor(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH);
}

void activateBuzzer() {
  digitalWrite(buzzerPin, HIGH);
}

void deactivateBuzzer() {
  digitalWrite(buzzerPin, LOW);
}
