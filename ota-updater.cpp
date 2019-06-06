#include <ArduinoOTA.h>  // To manage over-the-air updates of new code.

#include "ota-updater.h"

void OTAUpdater::initialize(const char* hostName, const char* password, IftttClient &ifttt, StatusLed &statusLed) {
  ArduinoOTA.setHostname(hostName);
  ArduinoOTA.setPassword(password);

  // The "[&]" is responsible for variable capture for lambda functions in C++ 11 (Read more: https://www.cprogramming.com/c++11/c++11-lambda-closures.html)
  ArduinoOTA.onStart([&]() {
    statusLed.onOtaUpdateStarted();
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_SPIFFS
      type = "filesystem";
    }

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Updater: Start updating " + type);
    ifttt.triggerEvent(IFTTT_WEBHOOK_EVENT_NAME, "Update started", "An over-the-air update has been started on your device.");
  });

  ArduinoOTA.onEnd([&]() {
    statusLed.onOtaUpdateEnded();
    ifttt.triggerEvent(IFTTT_WEBHOOK_EVENT_NAME, "Update ended", "The over-the-air update has been finished on your device.");
    Serial.println("\nUpdater: Ended.");
  });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Updater: Progress %u%%\r", (progress / (total / 100)));
  });

  ArduinoOTA.onError([&](ota_error_t error) {
    statusLed.onOtaUpdateFailed();
    Serial.printf("Updater: Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Updater: Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Updater: Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Updater: Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Updater: Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("Updater: End Failed");
    }

    ifttt.triggerEvent(IFTTT_WEBHOOK_EVENT_NAME, "Update failed", "The over-the-air update has been failed on your device.");
  });

  ArduinoOTA.begin();
}

void OTAUpdater::handleUpdateRequests() {
  ArduinoOTA.handle();
}