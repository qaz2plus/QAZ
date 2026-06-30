const int ledA = 2;
const int ledB = 5;
int valA = 0;    // A灯亮度 0~255
int step = 1;

void setup() {
  pinMode(ledA, OUTPUT);
  pinMode(ledB, OUTPUT);
}

void loop() {
  valA += step;
  // 边界反转
  if(valA >= 255 || valA <= 0){
    step = -step;
  }
  // 反相亮度：A=valA，B=255-valA
  analogWrite(ledA, valA);
  analogWrite(ledB, 255 - valA);
  delay(5);
}