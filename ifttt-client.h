#include <Arduino.h>

#ifndef ifttt_client_h
#define ifttt_client_h

class IftttClient {
  public:
    void setApiKey(String apiKey);
    void setDeviceName(String deviceName);
    void triggerEvent(String eventName, String title, String message);

  private:
    String _apiKey;
    String _deviceName;
    void triggerRawEvent(String eventName, String value1, String value2, String value3);
};

#endif /* ifttt_client_h */