#include <ESP8266WiFi.h>

// Update these with values suitable for your network.
const char* ssid = "REPLACE_SSID";
const char* password = "REPLACE_WIFI_PASS";

WiFiClient espClient;

void setup_wifi() {

  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Wi-Fi auth here
  WiFi.begin(ssid, password);

  // While Wi-Fi is connecting, wait
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("Wi-Fi connected");
  Serial.println("IP address: ");
  // Print assigned IP
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
}

void loop() {
  Serial.println("I'm connected to");
  Serial.println(ssid);
  delay(1000);  
}