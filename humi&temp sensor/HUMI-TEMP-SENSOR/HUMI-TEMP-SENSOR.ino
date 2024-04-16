#include <Arduino.h>
#include <DHT.h>

#define DHTPIN 5 // Assuming GPIO5 is correctly mapped to your ESP32 physical pin
#define DHTTYPE DHT22 // Use DHT22

DHT my_sensor(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  my_sensor.begin();
  Serial.println("DHT22 sensor initialization complete.");
}

void loop() {
  // Read humidity and temperature values
  float humidity = my_sensor.readHumidity();
  float temperature = my_sensor.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print("°C / Humidity: ");
    Serial.print(humidity);
    Serial.println("%");
  }

  delay(2000); // Wait a few seconds between measurements.
}
