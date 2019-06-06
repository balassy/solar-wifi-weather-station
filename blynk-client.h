#include <Arduino.h>

#ifndef blynk_client_h
#define blynk_client_h

class BlynkClient {
 public:
  void setAuthToken(const char* authToken);
  void waitUntilConnected();
  void sendUpdate(float temperature, float humidity, float voltage);
  void handleLoop();
};

#endif /* blynk_client_h */