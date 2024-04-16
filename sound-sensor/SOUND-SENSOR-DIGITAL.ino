#include <WiFi.h>

#define RXD2 16 // RX of Serial2
#define TXD2 17 // TX of Serial2

byte addArray[] = {
  0xFF, 0x01, 0x86,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x79
};

char dataValue[9];

void setup() {
  Serial.begin(9600); // initialization of Serial;
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2); // Set the baudrate for Serial2 for MH-Z14

  delay(500);
  Serial.println("Test code for MH-Z14");
}

void loop() {
  int co2 = 0;

  Serial2.write(addArray, 9);

  // Wait for response
  delay(100);

  // Read bytes one by one
  for (int i = 0; i < 9; i++) {
    while (!Serial2.available()); // Wait until data is available
    dataValue[i] = Serial2.read();
  }

  co2 = (256 * (int)dataValue[2]) + (int)dataValue[3]; // Formula for CO2 divided into 2 bytes

  Serial.print("CO2 value: ");
  Serial.print(co2);
  Serial.println(" ppm");
  delay(2000);
}
