#include <WiFi.h>
#include "DHT.h"

// =========================
// Wi-Fi settings
// =========================
const char* ssid = "iPhone (2)";
const char* password = "Wedela@2504";

// =========================
// DHT sensor settings
// =========================
#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// Create web server on port 80
WiFiServer server(80);

void setup() {

  Serial.begin(115200);

  // Start DHT sensor
  dht.begin();

  // Connect to Wi-Fi
  Serial.println();
  Serial.print("Connecting to Wi-Fi");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi connected!");

  // Print ESP32 IP address
  Serial.print("ESP32 IP address: ");
  Serial.println(WiFi.localIP());

  // Start server
  server.begin();

  Serial.println("Web server started!");
}

void loop() {

  WiFiClient client = server.available();

  if (client) {

    Serial.println("New client connected.");

    // Wait for client request
    String currentLine = "";

    while (client.connected()) {

      if (client.available()) {

        char c = client.read();

        if (c == '\n') {

          if (currentLine.length() == 0) {

            // Read sensor
            float temperature = dht.readTemperature();
            float humidity = dht.readHumidity();

            // Send HTTP response
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // HTML webpage
            client.println("<!DOCTYPE html>");
            client.println("<html>");
            client.println("<head>");

            client.println("<meta name='viewport' content='width=device-width, initial-scale=1'>");

            // Automatically refresh every 5 seconds
            client.println("<meta http-equiv='refresh' content='5'>");

            client.println("<title>Smart Temperature Monitor</title>");

            client.println("<style>");

            client.println("body {");
            client.println("font-family: Arial;");
            client.println("text-align: center;");
            client.println("background-color: #f2f2f2;");
            client.println("padding-top: 50px;");
            client.println("}");

            client.println(".card {");
            client.println("background: white;");
            client.println("width: 80%;");
            client.println("max-width: 400px;");
            client.println("margin: auto;");
            client.println("padding: 30px;");
            client.println("border-radius: 20px;");
            client.println("box-shadow: 0 4px 10px rgba(0,0,0,0.2);");
            client.println("}");

            client.println(".temperature {");
            client.println("font-size: 50px;");
            client.println("font-weight: bold;");
            client.println("}");

            client.println(".humidity {");
            client.println("font-size: 25px;");
            client.println("}");

            client.println("</style>");

            client.println("</head>");

            client.println("<body>");

            client.println("<div class='card'>");

            client.println("<h1>Smart Temperature Monitor</h1>");

            client.println("<h2>Room Temperature</h2>");

            client.print("<div class='temperature'>");
            client.print(temperature);
            client.println("°C</div>");

            client.println("<h2>Humidity</h2>");

            client.print("<div class='humidity'>");
            client.print(humidity);
            client.println(" %</div>");

            client.println("<p>Updates every 5 seconds</p>");

            client.println("</div>");

            client.println("</body>");

            client.println("</html>");

            client.println();

            break;
          }

          else {
            currentLine = "";
          }

        }

        else if (c != '\r') {
          currentLine += c;
        }
      }
    }

    client.stop();

    Serial.println("Client disconnected.");
  }
}
