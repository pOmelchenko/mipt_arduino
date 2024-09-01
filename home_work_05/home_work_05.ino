#include <Wire.h>

#define AHT20_ADDRESS 0x38

void setup() {
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  // 1. After power-on, wait for ≥100ms Before reading the temperature and humidity value, 
  // get a byte of status word by sending 0x71. If the status word and 0x18 are not equal 
  // to 0x18, initialize the 0x1B, 0x1C, 0x1E registers, details Please refer to our 
  // official website routine for the initialization process; if they are equal, proceed 
  // to the next step.
  delay(40);
  Wire.begin();
  Wire.beginTransmission(AHT20_ADDRESS);
  Wire.write(0x71);
  Wire.endTransmission();
  
  Wire.requestFrom(AHT20_ADDRESS, 1);
  while (Wire.available() == 0);
  uint8_t status = Wire.read();
  if (status & (1 << 3)) {
    Serial.println("calibration ok");
  } else {
    // вообще не понял что тут нужно сделать, если в это условие я всё таки попаду...
    Serial.println("Initialization required");
    return;
  }

  // 2. Wait 10ms to send the 0xAC command (trigger measurement). This command parameter has
  // two bytes, the first byte is 0x33, and the second byte is 0x00.
  delay(10);
  Wire.beginTransmission(AHT20_ADDRESS);
  Wire.write(0xAC);
  Wire.write(0x33);
  Wire.write(0x00);
  Wire.endTransmission();

  // 3. Wait 80ms for the measurement to be completed, if the read status word Bit[7] is 0, 
  // it means the measurement is completed, and then six bytes can be read continuously; 
  // otherwise, continue to wait.
  delay(80);
  Wire.requestFrom(AHT20_ADDRESS, 1);
  while (Wire.available() == 0);

  uint8_t response = Wire.read();
  if (!(response & (1 << 7))) {
    Serial.println("read ok");
  } else {
    Serial.println("data not readed");
    return;
  }

  Wire.requestFrom(AHT20_ADDRESS, 6);

  // Дальше была копипаста из библиотеки, так как было лениво заниматься преобразованиями
  int32_t temperature = 0;
  int32_t humidity = 0;
  uint32_t incoming = 0;

  Wire.read();

  incoming |= (uint32_t) Wire.read() << (8 * 2);
  incoming |= (uint32_t)Wire.read() << (8 * 1);
  uint8_t midByte = Wire.read();
  
  incoming |= midByte;
  humidity = incoming >> 4;

  temperature = (uint32_t)midByte << (8 * 2);
  temperature |= (uint32_t)Wire.read() << (8 * 1);
  temperature |= (uint32_t)Wire.read() << (8 * 0);

  temperature = temperature & ~(0xFFF00000);

  float tempCelsius = ((float)temperature / 1048576) * 200 - 50;
  Serial.print("temperature: ");
  Serial.println(tempCelsius);

  float relHumidity = ((float)humidity / 1048576) * 100;
  Serial.print("humidity: "); 
  Serial.println(relHumidity);

  Serial.println("End...");
  delay(2000);
}
