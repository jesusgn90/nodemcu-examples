#include <DHT.h>

// The NodeMCU pin (D2) for the data output from DHT11
#define DHT11_PIN 2

DHT DHT(DHT11_PIN, DHT11);

void setup()
{
    // Set baud to this value when reading serial monitor
    Serial.begin(115200);
    // Init DHT
    DHT.begin();
}

// The loop method, this runs all the time. 
void loop()
{
    // Read temperature in celsius
    float tempC = DHT.readTemperature();
    // Convert to Fahrenheit
    float tempF = DHT.convertCtoF(tempC);
    // Read humidity
    float humidity = DHT.readHumidity();

    // Celsius (ºC)
    Serial.print("Temperature (C) = ");
    Serial.println(tempC);

    // Fahrenheit (F)
    Serial.print("Temperature (F) = ");
    Serial.println(tempF);

    // Relative humidity (%)
    Serial.print("Humidity = ");
    Serial.println(humidity);

    // Wait 3 seconds before next iteration
    delay(3000);
}