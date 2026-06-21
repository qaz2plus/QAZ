// Define LED pin, ESP32 built-in LED is connected to GPIO 2
const int ledPin = 2; 

void setup() {
  // Initialize serial communication, baud rate set to 115200
  Serial.begin(115200);
  // Set LED pin to output mode
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // ========== SOS light logic ==========
  // S: 3 short flashes
  Serial.println("Send letter S (3 short flashes)");
  for(int i = 0; i < 3; i++) {
    digitalWrite(ledPin, HIGH);
    Serial.print("Short light ");
    Serial.println(i+1);
    delay(200);
    
    digitalWrite(ledPin, LOW);
    delay(200);
  }
  delay(500); // Interval between S and O
  
  // O: 3 long flashes
  Serial.println("Send letter O (3 long flashes)");
  for(int i = 0; i < 3; i++) {
    digitalWrite(ledPin, HIGH);
    Serial.print("Long light ");
    Serial.println(i+1);
    delay(600);
    
    digitalWrite(ledPin, LOW);
    delay(200);
  }
  delay(500); // Interval between O and S
  
  // S: 3 short flashes
  Serial.println("Send letter S (3 short flashes)");
  for(int i = 0; i < 3; i++) {
    digitalWrite(ledPin, HIGH);
    Serial.print("Short light ");
    Serial.println(i+1);
    delay(200);
    
    digitalWrite(ledPin, LOW);
    delay(200);
  }
  Serial.println("One group of SOS finished, wait 2 seconds to loop again");
  delay(2000); // Long pause after one full SOS cycle
}