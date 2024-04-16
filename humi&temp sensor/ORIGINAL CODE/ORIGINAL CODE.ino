/* 
  Sketch generated by the Arduino IoT Cloud Thing "Untitled 2"
  https://create.arduino.cc/cloud/things/a624c97b-9550-4a01-8e41-7d7c595f585b 

  Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made to the Thing

  CloudTemperatureSensor temperature;
  CloudRelativeHumidity humidity;

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/

#include "thingProperties.h"
#include <Arduino.h>
#include "DHT.h"
#include <DHT.h>

#define DHTPIN 5 // Assuming GPIO5 is correctly mapped to your ESP32 physical pin
#define DHTTYPE DHT22 // Use DHT22

DHT my_sensor(DHTPIN, DHTTYPE);

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
  */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  // Initialize DHT sensor
  my_sensor.begin();
}

void loop() {
  ArduinoCloud.update();
  // Your code here 
  float newHumidity = my_sensor.readHumidity();
  float newTemperature = my_sensor.readTemperature();

  if (isnan(newHumidity) || isnan(newTemperature)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Temperature: ");
    Serial.print(newTemperature);
    Serial.print("°C / Humidity: ");
    Serial.print(newHumidity);
    Serial.println("%");

    // Update cloud variables
    temperature = newTemperature;
    humidity = newHumidity;
  }

  delay(2000); // Wait a few seconds between measurements.
}

/*
  Since Humidity is READ_WRITE variable, onHumidityChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onHumidityChange()  {
  // Add your code here to act upon Humidity change
  Serial.print("New humidity received: ");
  Serial.println(humidity);
}

/*
  Since Temperature is READ_WRITE variable, onTemperatureChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onTemperatureChange()  {
  // Add your code here to act upon Temperature change
  Serial.print("New temperature received: ");
  Serial.println(temperature);
}

