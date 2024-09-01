#define LED_PWM 9

void setup() {
  Serial.begin(9600);
  pinMode(LED_PWM, OUTPUT);
}

float val = 0;

void loop() {
  uint16_t val = analogRead(A0);
  val = map(val, 0, 1023, 0, 255);
  analogWrite(LED_PWM, val);

  delay(100);
}
