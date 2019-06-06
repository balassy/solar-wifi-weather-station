#include <ESP8266HTTPClient.h>  // To send HTTP requests.

#include "ifttt-client.h"

void IftttClient::setApiKey(String apiKey) {
  _apiKey = apiKey;
}

void IftttClient::setDeviceName(String deviceName) {
  _deviceName = deviceName;
}

void IftttClient::triggerEvent(String eventName, String title, String message) {
  triggerRawEvent(eventName, title, message, _deviceName);
}

void IftttClient::triggerRawEvent(String eventName, String value1, String value2, String value3) {
  String url = String("http://maker.ifttt.com/trigger/") + eventName + "/with/key/" + _apiKey;
  Serial.println("IftttClient: Sending POST request to " + url);

  String requestBody = "value1=" + value1 + "&value2=" + value2 + "&value3=" + value3;
  Serial.println("IftttClient: HTTP request body: " + requestBody);

  HTTPClient http;
  http.begin(url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  int statusCode = http.POST(requestBody);

  Serial.printf("IftttClient: Received HTTP status code: %d\r\n", statusCode);
  if (statusCode != HTTP_CODE_OK) {
    String responseBody = http.getString();
    Serial.println("IftttClient: Received HTTP response body: " + responseBody);
  }

  http.end();
}