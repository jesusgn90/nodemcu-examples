#include <Adafruit_BMP280.h> 
 
// Using 0x77 implies both CSB and SDO are connected to 3V3!
#define BMP280_I2C_ADDRESS  0x77

// initialize Adafruit BMP280 library
Adafruit_BMP280  bmp280;
 
void setup(void)
{
  Serial.begin(9600);
  delay(1000);
 
  /**
   * SDA connected to NodeMCU D2 pin, which is GPIO4
   * SCL connected to NodeMCU D1 pin, which is GPIO5
   */
  Wire.begin(4, 5);
  
  // initialize the BMP280 sensor
  while (bmp280.begin(BMP280_I2C_ADDRESS) == 0)
  {  // connection error or device address wrong!
    Serial.println("Could not initialize sensor, retrying now...");
    delay(1000);
  }
}
 
void loop()
{
  float pressure_Pa = bmp280.readPressure();             // Print pressure in Pa
  float pressure_hPa = pressure_Pa / 100.0F;             // Print pressure in hPa
  //float pressure_atm = pressure_Pa * 0.0000102;          // Print pressure in atm
  //float pressure_bar = pressure_Pa / 100000;             // Print pressure in bar
  //float pressure_Torr = pressure_Pa * 0.0075;            // Print pressure in Torr
  //float pressure_mmWS = pressure_Pa * 0.102;             // Print pressure in mmWS
  //float pressure_psi = pressure_Pa *0.000145;            // Print pressure in psi

  Serial.print("Pressure = ");
  Serial.print(pressure_hPa);                             // Replace with the desired unit
  Serial.println(" hPa");                                 // Replace with the desired unit

  delay(1000);
}
 
