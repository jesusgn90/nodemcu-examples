#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Broker port
#define MQTT_PORT 1884
#define BAUD_RATE 115200

// Update these with values suitable for your network.
const char* ssid = "REPLACE_SSID";
const char* password = "REPLACE_WIFI_PASS";

// Broker address (Raspberry Pi address)
const char *mqtt_server = "192.168.1.132";

// Publish topic
const char* publish_topic = "outTopic";

// Subscribe topic
const char* subscribe_topic = "inTopic";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

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
  Serial.println(WiFi.localIP());
}

// Logic for arrived messages
void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str()))
    {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish(publish_topic, "hello world");
      // ... and resubscribe
      client.subscribe(subscribe_topic);
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup()
{
  Serial.begin(BAUD_RATE);

  // Configure Wi-Fi connection
  setup_wifi();

  // Configure broker server
  client.setServer(mqtt_server, MQTT_PORT);

  // Set callback for arrived messages
  client.setCallback(callback);
}

void loop()
{
  // Connect the MQTT client
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();

  // Send "Hello world :value" message to the broker server
  // Here we can for example read sensor value and send it
  ++value;
  snprintf(msg, 50, "hello world #%ld", value);
  Serial.print("Publish message: ");
  Serial.println(msg);
  client.publish(publish_topic, msg);
  delay(2000)
}