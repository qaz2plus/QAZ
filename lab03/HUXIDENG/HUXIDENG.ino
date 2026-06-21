// Define LED pin, ESP32 built-in LED is GPIO 2
const int ledPin = 2;
// Time interval for 1Hz blink: 500ms on / 500ms off
const unsigned long interval = 500;
unsigned long previousTime = 0;
bool ledState = LOW;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Get current system running milliseconds
  unsigned long currentTime = millis();
  // Judge whether the interval time has passed
  if (currentTime - previousTime >= interval) {
    previousTime = currentTime;
    // Flip LED state
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
  }
}