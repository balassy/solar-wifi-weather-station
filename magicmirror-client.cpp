#include <ESP8266HTTPClient.h>  // To send HTTP requests.

#include "magicmirror-client.h"

void MagicMirrorClient::setHostUrl(String hostUrl) {
  _hostUrl = hostUrl;
}

void MagicMirrorClient::sendTemperature(float temperature, float humidity, float voltage) {
  // Calculate battery level percentage from voltage.
  float voltageMinLevel = 2.8;
  float voltageMaxLevel = 4.2;
  float voltageRange = voltageMaxLevel - voltageMinLevel;
  float voltageDelta = voltage - voltageMinLevel;
  float voltagePercentage = voltageDelta / voltageRange;
  int voltagePercentageRounded = round(voltagePercentage * 100);

  int temperatureRounded = round(temperature);
  int humidityRounded = round(humidity);

  String url = _hostUrl + "/remote-temperature";
  Serial.println("MagicMirrorClient: Sending POST request to MagicMirror at " + url);

  String requestBody = "{ \"temp\": " + String(temperatureRounded) + ", \"humidity\": " + String(humidityRounded) + ", \"battery\": " + String(voltagePercentageRounded) + " }";
  Serial.println("MagicMirrorClient: HTTP request body: " + requestBody);

  WiFiClient wifiClient;
  HTTPClient http;
  http.begin(wifiClient, url);
  http.addHeader("Content-Type", "application/json");
  
  int statusCode = http.POST(requestBody);

  Serial.printf("MagicMirrorClient: Received HTTP status code: %d\r\n", statusCode);
  if (statusCode != HTTP_CODE_OK) {
    String responseBody = http.getString();
    Serial.println("MagicMirrorClient: Received HTTP response body: " + responseBody);
  }

  http.end();
}