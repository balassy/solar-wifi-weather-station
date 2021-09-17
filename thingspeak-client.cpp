#include <ESP8266HTTPClient.h>  // To send HTTP requests.

#include "thingspeak-client.h"

void ThingSpeakClient::setApiKey(String apiKey) {
  _apiKey = apiKey;
}

void ThingSpeakClient::writeField(String field1Value, String field2Value, String field3Value, String statusMessage) {
  String url = String("http://api.thingspeak.com/update");
  Serial.println("ThingSpeakClient: Sending POST request to " + url);

  String requestBody = "api_key=" + _apiKey + "&field1=" + field1Value + "&field2=" + field2Value + "&field3=" + field3Value + "&status=" + statusMessage;
  Serial.println("ThingSpeakClient: HTTP request body: " + requestBody);

  WiFiClient wifiClient;
  HTTPClient http;
  http.begin(wifiClient, url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int statusCode = http.POST(requestBody);

  Serial.printf("ThingSpeakClient: Received HTTP status code: %d\r\n", statusCode);
  if (statusCode != HTTP_CODE_OK) {
    String responseBody = http.getString();
    Serial.println("ThingSpeakClient: Received HTTP response body: " + responseBody);
  }

  http.end();
}