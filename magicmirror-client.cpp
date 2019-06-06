#include <ESP8266HTTPClient.h>  // To send HTTP requests.

#include "magicmirror-client.h"

void MagicMirrorClient::setHostUrl(String hostUrl) {
  _hostUrl = hostUrl;
}

void MagicMirrorClient::sendTemperature(float temperature, float humidity) {
  String url = _hostUrl + "/remote-temperature";
  Serial.println("MagicMirrorClient: Sending POST request to MagicMirror at " + url);

  String requestBody = "{ \"temp\": " + String(temperature) + ", \"humidity\": " + String(humidity) + " }";
  Serial.println("MagicMirrorClient: HTTP request body: " + requestBody);

  HTTPClient http;
  http.begin(url);
  http.addHeader("Content-Type", "application/json");
  
  int statusCode = http.POST(requestBody);

  Serial.printf("MagicMirrorClient: Received HTTP status code: %d\r\n", statusCode);
  if (statusCode != HTTP_CODE_OK) {
    String responseBody = http.getString();
    Serial.println("MagicMirrorClient: Received HTTP response body: " + responseBody);
  }

  http.end();
}