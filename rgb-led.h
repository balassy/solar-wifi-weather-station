#include <Arduino.h>

#ifndef rgb_led_h
#define rgb_led_h

enum LedColor {
  Red,
  Green,
  Blue,
  Orange,
  Purple,
  Cyan,
  White
};

class RgbLed {
 public:
  void setPins(uint8_t redPin, uint8_t greenPin, uint8_t bluePin);
  void turnOn(LedColor color);
  void turnOff(LedColor color);

 private:
  uint8_t _redPin;
  uint8_t _greenPin;
  uint8_t _bluePin;
  void _turnOn(uint8_t pin);
  void _turnOff(uint8_t pin);
};

#endif /* rgb_led_h */