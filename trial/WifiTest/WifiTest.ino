#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

#define WIFI_CONNECTED 1
#define WIFI_DISCONNECTED 0

const char *ssid = "HOME";
const char *password = "147852369home";

const char *espssid = "esp1";
const char *esppass = "12345678";

// STATUS FLAGS
uint8_t wifiStatus;
bool softAPStatus; 
// STATUS FLAGS END

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
  if (softAPStatus) {
    Wifi.softAPdisconnect(true);
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

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');
  wifiStatus = WIFI_DISCONNECTED;
  softAPStatus = SOFT_AP_OFF;
  startAccessPoint();
  startEspStation();
}

void loop() {
  checkWiFiStatus();
}
