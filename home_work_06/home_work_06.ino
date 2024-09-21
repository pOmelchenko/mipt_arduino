#include "Adafruit_GFX.h" 
#include "Adafruit_ILI9341.h"
#include <Fonts/FreeSans12pt7b.h>
#include "URTouch.h"
#include <Wire.h>
#include <AHT20.h>

#define TFT_DC 9              
#define TFT_CS 10            
#define TFT_RST 8
#define TFT_MISO 12         
#define TFT_MOSI 11           
#define TFT_CLK 13            

Adafruit_ILI9341 display = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

#define t_SCK 3              
#define t_CS 4                
#define t_MOSI 5              
#define t_MISO 6             
#define t_IRQ 7              

URTouch ts(t_SCK, t_CS, t_MOSI, t_MISO, t_IRQ);

AHT20 aht20;

void setup(){
  Wire.begin(); //Join I2C bus
  //Check if the AHT20 will acknowledge
  if (aht20.begin() == false)
  {
    while (1);
  }

  display.begin();                     
  display.setRotation(1);           

  draw();
}

float old_val = 0;
 
void loop()                   
{
  if (aht20.available() == true)
  {
    //Get the new temperature and humidity value
    float temperature = aht20.getTemperature();
    float humidity = aht20.getHumidity();

    cleanValue(old_val);
    writeValue(temperature);
    old_val = temperature;
  }

  delay(1000);
}

static const unsigned char PROGMEM image_weather_humidity_bits[] = {0x04,0x00,0x04,0x00,0x0c,0x00,0x0e,0x00,0x1e,0x00,0x1f,0x00,0x3f,0x80,0x3f,0x80,0x7e,0xc0,0x7f,0x40,0xff,0x60,0xff,0xe0,0x7f,0xc0,0x7f,0xc0,0x3f,0x80,0x0f,0x00};
static const unsigned char PROGMEM image_weather_temperature_bits[] = {0x1c,0x00,0x22,0x02,0x2b,0x05,0x2a,0x02,0x2b,0x38,0x2a,0x60,0x2b,0x40,0x2a,0x40,0x2a,0x60,0x49,0x38,0x9c,0x80,0xae,0x80,0xbe,0x80,0x9c,0x80,0x41,0x00,0x3e,0x00};
void draw(void) {
    display.fillRect(0, 0, 320, 240, 0x0);
    display.drawRect(10, 190, 145, 40, 0x7BCF);
    display.drawRect(165, 190, 145, 40, 0x75C8);
    display.drawRect(10, 10, 300, 170, 0xFB40);
    display.setTextColor(0x75C8);
    display.setTextWrap(false);
    display.setFont(&FreeSans12pt7b);
    display.setCursor(212, 217);
    display.print("Temp");
    display.setTextColor(0x51A);
    display.setCursor(48, 217);
    display.print("Humid");
    display.drawBitmap(30, 202, image_weather_humidity_bits, 11, 16, 0x476);
    display.drawBitmap(185, 202, image_weather_temperature_bits, 16, 16, 0x75C8);
}


void writeValue(float value)
{
  display.setTextColor(0xC682);
  display.setTextSize(4);
  display.setCursor(52, 124);
  display.print(value);
}
void cleanValue(float value)
{
  display.setTextColor(0x0);
  display.setTextSize(4);
  display.setCursor(52, 124);
  display.print(value);
}
