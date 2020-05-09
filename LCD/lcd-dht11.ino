// ESP8266 or ARDUINO with 16x2 i2c LCD
// Compatible with the Arduino IDE 1.8.3
// Library https://github.com/lucasmaziero/LiquidCrystal_I2C
// Original Library https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library
// Standard for ESP8266 with 4-SDA 5-SCL or ARDUINO with A4-SDA A5-SCL and LCD 16x2 display
// and access from ESP8266: lcd.begin(sda,scl) or ARDUINO: lcd.begin()
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// The NodeMCU pin (D2) for the data output from DHT11
#define DHT11_PIN 2

DHT DHT(DHT11_PIN, DHT11);

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

char tstr[100];
char hstr[100];

void setup()
{
  DHT.begin();
  lcd.begin();
  delay(10);
  lcd.backlight();  
}

void loop()
{
  float T = DHT.readTemperature();
  float H = DHT.readHumidity();

  snprintf(tstr, 50, "Temp: %2.2fC", T);
  snprintf(hstr, 50, "Hum: %2.2f", H);
  
  lcd.setCursor(0, 0);
  lcd.print(tstr);

  lcd.setCursor(0, 1);
  lcd.print(hstr);
 
  delay(2000);
}