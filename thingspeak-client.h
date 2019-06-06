#include <Arduino.h>

#ifndef thingspeak_client_h
#define thingspeak_client_h

class ThingSpeakClient {
 public:
  void setApiKey(String apiKey);
  void writeField(String field1Value, String field2Value, String field3Value, String statusMessage);

 private:
  String _apiKey;
};

#endif /* thingspeak_client_h */