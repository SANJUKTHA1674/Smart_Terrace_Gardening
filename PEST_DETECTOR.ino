#define TRIG_PIN 2
#define ECHO_PIN 3
#define BUZZER_PIN 4
#include <Servo.h>

Servo myservo; // Create a Servo object

int lm35Pin = A0; // LM35 temperature sensor input pin
int rainSensorPin = 2; // Rain sensor input pin
int thresholdTemperature = 25; // Threshold temperature in Celsius
int thresholdRainValue = 500; // Threshold value for rain detection

void setup() {
  myservo.attach(9); // Attach the servo to pin 9
  pinMode(rainSensorPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  int temperature = readTemperature();
  int rainValue = digitalRead(rainSensorPin);

  if (temperature > thresholdTemperature && rainValue < thresholdRainValue) {
    // If both conditions are met, rotate the servo to 180 degrees
    myservo.write(180);
    delay(1000); // Delay to allow the servo to reach its position
    myservo.write(0); // Return the servo to 0 degrees
  }
  else {
    // If the conditions are not met, keep the servo at 0 degrees
    myservo.write(0);
  }
}

int readTemperature() {
  int rawValue = analogRead(lm35Pin);
  float voltage = (rawValue / 1024.0) * 5.0; // Convert raw value to voltage
  float temperatureCelsius = (voltage - 0.5) * 100.0; // Convert voltage to temperature in Celsius
  return int(temperatureCelsius);
}

long duration;
int distance;
int alertDistance = 20; // Adjust this distance as needed for your application (in centimeters)

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Clear the trigger pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  
  // Send a 10μs pulse to trigger the ultrasonic sensor
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Read the duration of the echo pulse
  duration = pulseIn(ECHO_PIN, HIGH);
  
  // Calculate the distance in centimeters
  distance = duration * 0.034 / 2;
  
  // Print the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // Check if an object is too close and activate the buzzer
  if (distance <= alertDistance) {
    digitalWrite(BUZZER_PIN, HIGH); // Turn on the buzzer
  } else {
    digitalWrite(BUZZER_PIN, LOW); // Turn off the buzzer
  }
  
  delay(500); // Delay between readings (adjust as needed)
}


