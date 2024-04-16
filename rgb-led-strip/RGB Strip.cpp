#include <Adafruit_NeoPixel.h>

#define PIN 6         // Data pin that the NeoPixel is attached to
#define NUM_LEDS 30   // Number of LEDs in the strip

// Initialize the NeoPixel strip
Adafruit_NeoPixel strip(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();           // Initialize the strip
  strip.show();            // Initialize all pixels to 'off'
}

void loop() {
  colorWipe(strip.Color(255, 0, 0), 50); // Red
  colorWipe(strip.Color(0, 255, 0), 50); // Green
  colorWipe(strip.Color(0, 0, 255), 50); // Blue
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t color, int wait) {
  for(int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}
