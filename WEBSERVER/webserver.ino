// Base from https://randomnerdtutorials.com/esp8266-nodemcu-static-fixed-ip-address-arduino/
#include <ESP8266WiFi.h>

// Replace with your network credentials
const char* ssid     = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASS";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Aux variables for the loop
unsigned long currentTime = millis();
unsigned long previousTime = 0;
// Define timeout time in milliseconds
const unsigned short timeoutTime = 2000;

// Static IP (optional)
IPAddress local_IP(192, 168, 1, 184);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

void setup() {
  Serial.begin(9600);

  // Configures static IP address (optional)
  while (!WiFi.config(local_IP, gateway, subnet)) {
    delay(500);
  }

  // Connect to Wi-Fi network with SSID and password
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  server.begin();
}

void handleRequest(WiFiClient client, float outputValue) {
  String currentLine = "";                // make a String to hold incoming data from the client
  currentTime = millis();
  previousTime = currentTime;
  while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
    currentTime = millis();
    if (client.available()) {             // if there's bytes to read from the client,
      char c = client.read();             // read a byte, then
      Serial.write(c);                    // print it out the serial monitor
      header += c;
      if (c == '\n') {                    // if the byte is a newline character
        // if the current line is blank, you got two newline characters in a row.
        // that's the end of the client HTTP request, so send a response:
        if (currentLine.length() == 0) {
          // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
          // and a content-type so the client knows what's coming, then a blank line:
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println("Connection: close");
          client.println();

          // Document open
          client.println("<!DOCTYPE html><html>");

          // Headers
          client.println("<head>");
          client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
          client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}</style>");
          client.println("</head>");

          // Body
          client.println("<body>");
          client.println("<h1>ESP8266 Web Server</h1>");
          client.println(String(outputValue));
          client.println("</body>");

          // Document closes
          client.println("</html>");

          // The HTTP response ends with another blank line
          client.println();
          // Break out of the while loop
          break;
        } else { // if you got a newline, then clear currentLine
          currentLine = "";
        }
      } else if (c != '\r') {  // if you got anything else but a carriage return character,
        currentLine += c;      // add it to the end of the currentLine
      }
    }
  }
  // Clear the header variable
  header = "";
  // Close the connection
  client.stop();
}

void loop() {
  WiFiClient client = server.available();   // Listen for incoming clients
  float valueReadFromSensor = 1.07;
  if (client) handleRequest(client, valueReadFromSensor);
}