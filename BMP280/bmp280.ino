#include <Adafruit_BMP280.h>

// Using 0x77 implies both CSB and SDO are connected to 3V3!
#define BMP280_I2C_ADDRESS  0x77

// initialize Adafruit BMP280 library
Adafruit_BMP280  bmp280;

typedef enum {Pa, hPa, atm, bar, Torr, mmWS, psi} UNIT; // Available measurement units

UNIT unit = hPa; // Replace with the desired unit

void setup()
{
  Serial.begin(9600);
  delay(1000);

  /*
     SDA connected to NodeMCU D2 pin, which is GPIO4
     SCL connected to NodeMCU D1 pin, which is GPIO5
  */
  Wire.begin(4, 5);

  // initialize the BMP280 sensor
  while (bmp280.begin(BMP280_I2C_ADDRESS) == 0)
  {
    // connection error or device address wrong!
    Serial.println("Could not initialize sensor, retrying now...");
    delay(1000);
  }
}

void loop()
{
  float pressure = bmp280.readPressure();  // Defaults Pa

  switch (unit) {

    case hPa:
      pressure /= 100.0F;
      break;

    case atm:
      pressure *= 0.0000102F;
      break;

    case bar:
      pressure /= 100000;
      break;

    case Torr:
      pressure *= 0.0075;
      break;

    case mmWS:
      pressure *= 0.102;
      break;

    case psi:
      pressure *= 0.000145;
      break;
  }

  delay(1000);

}
