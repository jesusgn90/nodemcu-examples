#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// The NodeMCU pin (D4) for the data output from DHT11
#define DHT11_PIN 2

DHT DHT(DHT11_PIN, DHT11);

// Broker port
#define MQTT_PORT 1884

// Sleep time
#define SLEEP_TIME 120000

// Baud rate
#define BAUD_RATE 115200

// Update these with values suitable for your network.
const char* ssid = "SSD";
const char* password = "PASSWORD";

// Broker address (Raspberry Pi address)
const char *mqtt_server = "192.168.1.132";

// Publish topic
const char* publish_topic = "NODEMCUDHTHOME01";

// Wi-Fi client
WiFiClient espClient;

// MQTT client
PubSubClient client(espClient);

// String for sending the data
char msg[100];

void setup_wifi()
{

  delay(10);
  // We start by connecting to a WiFi network
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }

  randomSeed(micros());

  // NodeMCU address
  // Serial.println(WiFi.localIP());
}

void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    // Create a random client ID
    String clientId = "NODEMCUHOME01-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (!client.connect(clientId.c_str()))
    {
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void processData()
{
  // Connect the MQTT client
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();

  // Read temperature in celsius
  float T = DHT.readTemperature();
  // Read humidity
  float H = DHT.readHumidity();

  snprintf(msg, 50, "{\"humidity\": %2.2f, \"temperature\": %2.2f}", H, T);
  Serial.println(msg);
  client.publish(publish_topic, msg);
  delay(2000);
}

void setup()
{
  Serial.begin(BAUD_RATE);
  // Init DHT
  DHT.begin();
}

void loop()
{
    // Configure Wi-Fi connection
  setup_wifi();

  // Configure broker server
  client.setServer(mqtt_server, MQTT_PORT);

  // Read sensor, send MQTT message
  processData();

  // Save battery here!
  WiFi.disconnect();
  client.disconnect();

  delay(SLEEP_TIME);
}