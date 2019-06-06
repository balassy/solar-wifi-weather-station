#include <Arduino.h>
#include "rgb-led.h"

#ifndef status_led_h
#define status_led_h

class StatusLed {
 public:
  void setPins(uint8_t redPin, uint8_t greenPin, uint8_t bluePin);
  void onBootStarted();
  void onBootEnded();
  void onWebrequestStarted();
  void onWebrequestEnded();
  void onMeasurementStarted();
  void onMeasurementEnded();
  void onOtaUpdateStarted();
  void onOtaUpdateEnded();
  void onOtaUpdateFailed();
  void onWifiManagerAccessPointModeStarted();
  void onWifiManagerAccessPointModeEnded();

 private:
  RgbLed _led;
};

#endif /* status_led_h */