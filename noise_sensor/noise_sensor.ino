// Define the pin where the noise sensor is connected
const int noiseSensorPin = A0;

void setup() {
  // Initialize serial communication
  pinMode (noiseSensorPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // Read the analog value from the noise sensor
  int noiseLevel = analogRead(noiseSensorPin);

  // Print the noise level to the serial monitor
  Serial.print("Noise Level: ");
  Serial.println(noiseLevel);

  // You can add additional logic here based on the noise level read
  // For example, triggering an action if the noise level exceeds a certain threshold
  
  delay(1000); // Delay to make readings less frequent (adjust as needed)
}
