#include "status-led.h"

void StatusLed::setPins(uint8_t redPin, uint8_t greenPin, uint8_t bluePin) {
  _led.setPins(redPin, greenPin, bluePin);
}

void StatusLed::onBootStarted() {
  _led.turnOn(LedColor::Blue);
}

void StatusLed::onBootEnded() {
  _led.turnOff(LedColor::Blue);
}

void StatusLed::onWebrequestStarted() {
  _led.turnOn(LedColor::Green);
}

void StatusLed::onWebrequestEnded() {
  _led.turnOff(LedColor::Green);
}

void StatusLed::onMeasurementStarted() {
  _led.turnOn(LedColor::Green);
}

void StatusLed::onMeasurementEnded() {
  _led.turnOff(LedColor::Green);
}

void StatusLed::onOtaUpdateStarted() {
  _led.turnOff(LedColor::White);
  _led.turnOn(LedColor::Orange);
}

void StatusLed::onOtaUpdateEnded() {
  _led.turnOff(LedColor::Orange);
}

void StatusLed::onOtaUpdateFailed() {
  _led.turnOn(LedColor::Red);
}

void StatusLed::onWifiManagerAccessPointModeStarted() {
  _led.turnOff(LedColor::White);
  _led.turnOn(LedColor::Orange);
}

void StatusLed::onWifiManagerAccessPointModeEnded() {
  _led.turnOff(LedColor::Orange);
}
