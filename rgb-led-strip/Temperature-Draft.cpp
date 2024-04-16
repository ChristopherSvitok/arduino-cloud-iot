#include <Adafruit_NeoPixel.h>

#define PIN 6          // NeoPixel strip connected to digital pin 6
#define NUM_LEDS 10    // Number of LEDs in the strip

Adafruit_NeoPixel strip(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(100); // Set brightness to a medium level (0-255)
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Simulate temperature change
  for(int temp = 15; temp <= 25; temp++) { // Temperature goes up
    updateStripBasedOnTemperature(temp);
    delay(500); // Wait half a second
  }
  for(int temp = 25; temp >= 15; temp--) { // Temperature goes down
    updateStripBasedOnTemperature(temp);
    delay(500); // Wait half a second
  }
}

void updateStripBasedOnTemperature(int temp) {
  // Calculate the position based on temperature
  int position = map(temp, 15, 25, 0, NUM_LEDS - 1);
  
  // Clear the strip
  for(int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0)); // Turn off all LEDs
  }
  
  // Set the color of the LEDs up to the current position
  for(int i = 0; i <= position; i++) {
    // Calculate color
    // At the start (cold), we want blue: (0, 0, 255)
    // At the end (hot), we want red: (255, 0, 0)
    int red = map(i, 0, NUM_LEDS - 1, 0, 255);
    int blue = 255 - red;
    strip.setPixelColor(i, strip.Color(red, 0, blue));
  }
  
  strip.show(); // Update the strip with new colors
}

// Helper function to generate color values
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
