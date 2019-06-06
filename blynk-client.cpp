#define BLYNK_PRINT Serial

#include <BlynkSimpleEsp8266.h>  // To communicate with the Blynk service re-using the existing WiFi connection.

#include "blynk-client.h"

void BlynkClient::setAuthToken(const char* authToken) {
  Blynk.config(authToken);
}

void BlynkClient::waitUntilConnected() {
  while (!Blynk.connect()) {
    delay(500);
    Serial.print(F("."));
  }
}

void BlynkClient::sendUpdate(float temperature, float humidity, float voltage) {
  Blynk.virtualWrite(V16, temperature);
  Blynk.virtualWrite(V17, humidity);
  Blynk.virtualWrite(V18, voltage);
}

void BlynkClient::handleLoop() {
  Blynk.run();
}