int IRpin = 16;
unsigned long high_time = 500000;
unsigned long period = 660000 + high_time;
long t = micros();

void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  pinMode(16, OUTPUT);
  analogWriteFreq(40000);
  analogWriteRange(255);
}

void loop() {
  if (micros() - t < high_time) {
    analogWrite(16, 85);
  } else {
    analogWrite(16, 0);
  }
  if (micros() - t >= period)
    t = micros();
}
