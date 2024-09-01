#define K 0.1

float expRunningAverage(float newVal);

void setup() {
  Serial.begin(9600);
}

float val = 0;

void loop() {
  int val = analogRead(A0);

  Serial.print(val);
  Serial.print(" ");

  val = (int) expRunningAverage((float) val);

  Serial.print(val);
  Serial.print(" ");

  val = map(val, 0, 1023, 0, 10);

  Serial.println(val);

  delay(100);
}


// бегущее среднее
float expRunningAverage(float newVal) {
  static float filVal = 0;
  filVal += (newVal - filVal) * K;
  return filVal;
}