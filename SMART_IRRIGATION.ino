#define MOISTURE_SENSOR A0
#define RELAY_PIN 2

int moistureThreshold = 500; // Adjust this value based on your soil and plant needs

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Turn off the water pump initially
  Serial.begin(9600);
}

void loop() {
  int moistureLevel = analogRead(MOISTURE_SENSOR);

  Serial.print("Moisture Level: ");
  Serial.println(moistureLevel);

  if (moistureLevel < moistureThreshold) {
    Serial.println("Soil is dry. Turning on water pump and valve.");
    digitalWrite(RELAY_PIN, HIGH); // Turn on the relay to activate the water pump and valve
    delay(10000); // Run the pump and valve for 10 seconds (adjust as needed)
    digitalWrite(RELAY_PIN, LOW); // Turn off the relay
    Serial.println("Watering complete.");
  }

  delay(60000); // Wait for 1 minute before checking again (adjust as needed)
}

