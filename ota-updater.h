#include <Arduino.h>

#ifndef ota_updater_h
#define ota_updater_h

#include "ifttt-client.h"
#include "status-led.h"

extern const char* IFTTT_WEBHOOK_EVENT_NAME;

class OTAUpdater {
 public:
  void initialize(const char* hostName, const char* password, IftttClient &ifttt, StatusLed &statusLed);
  void handleUpdateRequests();
};

#endif /* ota_updater_h */