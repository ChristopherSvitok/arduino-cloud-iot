/*
  Sketch generated by the Arduino IoT Cloud Thing "Untitled 2"
  https://create.arduino.cc/cloud/things/a624c97b-9550-4a01-8e41-7d7c595f585b

  Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made to the Thing

  float air_quality;
  CloudTemperatureSensor temperature;
  int general_air_quality;
  int light;
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

//#include<AirQuality.h>
//#include"AirQuality.h"

//AirQuality airqualitysensor;
//int current_quality =-1;
  int 

//DUST SENSOR
int pin_dust = 18;
unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 30000;//sample 30s ;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;
//DUST SENSOR
int lightsensor = 36;


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
  //DUST SENSOR
  pinMode(pin_dust,INPUT);
  starttime = millis();//get the current time;
  //DUST SENSOR

    //AIR QUALITY SENSOR
    //airqualitysensor.init(17);
    
    //Light Sensor
    pinMode(lightsensor,INPUT);
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


  //DUST SENSOR
      duration = pulseIn(pin-dust, LOW);
    lowpulseoccupancy = lowpulseoccupancy+duration;

    if ((millis()-starttime) > sampletime_ms)//if the sample time == 30s
    {
        ratio = lowpulseoccupancy/(sampletime_ms*10.0);  // Integer percentage 0=>100
        concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
        //Serial.print(lowpulseoccupancy);
        //Serial.print(",");
        //Serial.print(ratio);
        //Serial.print(",");
        Serial.print(concentration);
        Serial.print("Concentration: ");
        lowpulseoccupancy = 0;
        starttime = millis();
        //Update cloud variables
        air_quality = concentration;
    }
    //DUST SENSOR
    
 
    
    
    //LIGHT SENSOR
    int lightsensorvalue = analogRead(lightsensor);
    Serial.print("Light Sensor Value: ");
    Serial.println(lightsensorvalue);
    int light = lightsensorvalue;


  delay(2000); // Wait a few seconds between measurements.
}

