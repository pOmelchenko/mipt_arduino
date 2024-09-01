#define RED_LED 8
#define YELLOW_LED 9
#define GREEN_LED 10

void setup() {
  Serial.begin(9600);
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
}

float val = 0;

void loop() {
  int val = analogRead(A0);

  Serial.print(val);
  Serial.print(" ");

  val = map(val, 0, 1023, 0, 10);

  Serial.println(val);

  delay(100);
}

