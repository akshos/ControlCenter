#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#define WIFI_CONNECTED 1
#define WIFI_DISCONNECTED 0

#define RELAY_1 14 //D5
#define RELAY_2 12 //D6

uint8_t relay_pins[] = {RELAY_1, RELAY_2};

const char *ssid = "HOME";
const char *password = "147852369home";

const char *espssid = "esp1";
const char *esppass = "12345678";

// STATUS FLAGS
uint8_t wifiStatus;
bool softAPStatus; 
// STATUS FLAGS END

ESP8266WebServer server(80);

bool startAccessPoint() {
  Serial.println("Starting ESP9266 SoftAP..");
  //WiFi.softAP(ssid, password, channel, hidden, max_connection)
  if (WiFi.softAP(espssid, esppass, 1, true, 4)) {
    Serial.print("ESP SSID : "); Serial.println(espssid);
    Serial.print("ESP IP Address : "); Serial.println(WiFi.softAPIP());
    return true;
  }
  Serial.println("Failed to start access point");
  return false;
}

void stopAccessPoint() {
  Serial.println("Stopping AP mode...");
  if (softAPStatus) {
    WiFi.softAPdisconnect(true);
  }
}

void startEspStation() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.println(WiFi.SSID());
}

void checkWiFiStatus() {
  if (wifiStatus == WIFI_DISCONNECTED && WiFi.status() == WL_CONNECTED) {
    Serial.print("WiFi Connected : ");
    Serial.print(WiFi.SSID()); Serial.print(" : ");
    Serial.println(WiFi.localIP());
    wifiStatus = WIFI_CONNECTED;
    stopAccessPoint();
  }
  else if (wifiStatus == WIFI_CONNECTED && WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi connection lost");
    wifiStatus = WIFI_DISCONNECTED;
    softAPStatus = startAccessPoint();
  }
}

void handleRoot() {
  server.send(200, "text/plain", "<html><body><h1>Hello World</h1></body></html>");
}

void handleNotFound() {
  server.send(404, "text/plain", "<html><body><h1>404: Not found</h1>/body></html>");
}

void handleRelay() {
  if (server.method() == HTTP_POST) {
    if (server.hasArg("relay") && server.hasArg("state")) {
      uint8_t relayPin = relay_pins[server.arg("relay").toInt()];
      digitalWrite(relayPin,  server.arg("state").toInt());
      server.send(200, "text/plain", "processed");
    }
  }
}

void setupHttpHandlers() {
  server.on("/", handleRoot);
  server.on("/relay", handleRelay);
  server.onNotFound(handleNotFound);
}

void setup() {
  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');
  wifiStatus = WIFI_DISCONNECTED;
  softAPStatus = startAccessPoint();
  startEspStation();
  Serial.println("Starting HTTP Server");
  setupHttpHandlers();
  server.begin();
}

void loop() {
  checkWiFiStatus();
  server.handleClient();
}
