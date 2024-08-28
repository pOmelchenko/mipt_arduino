#define BUTTON 2
#define LED 12

int led = LOW;

void setup() {
  // button
  pinMode(BUTTON, INPUT);

  // LED
  // red:
  // - Ud = 2V
  // - Id = 20 mA  = 0.02 A
  // - R = (Up - Ud) / Id = (5 - 2) / 0.02 = 150 Omh
  pinMode(LED, OUTPUT);
}

void loop() {
  if (digitalRead(BUTTON) == HIGH) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
}
