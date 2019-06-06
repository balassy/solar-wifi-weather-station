#include "rgb-led.h"

void RgbLed::setPins(uint8_t redPin, uint8_t greenPin, uint8_t bluePin) {
  _redPin = redPin;
  pinMode(redPin, OUTPUT);
  digitalWrite(redPin, HIGH);

  _greenPin = greenPin;
  pinMode(greenPin, OUTPUT);
  digitalWrite(greenPin, HIGH);

  _bluePin = bluePin;
  pinMode(bluePin, OUTPUT);
  digitalWrite(bluePin, HIGH);
}

void RgbLed::turnOn(LedColor color) {
  switch (color) {
    case LedColor::Red:
      _turnOn(_redPin);
      break;
    case LedColor::Green:
      _turnOn(_greenPin);
      break;
    case LedColor::Blue:
      _turnOn(_bluePin);
      break;
    case LedColor::Orange:
      _turnOn(_redPin);
      _turnOn(_greenPin);
      break;
    case LedColor::Purple:
      _turnOn(_redPin);
      _turnOn(_bluePin);
      break;
    case LedColor::Cyan:
      _turnOn(_greenPin);
      _turnOn(_bluePin);
      break;
    case LedColor::White:
      _turnOn(_redPin);
      _turnOn(_greenPin);
      _turnOn(_bluePin);
      break;
    default:
      break;
  }
}

void RgbLed::turnOff(LedColor color) {
  switch (color) {
    case LedColor::Red:
      _turnOff(_redPin);
      break;
    case LedColor::Green:
      _turnOff(_greenPin);
      break;
    case LedColor::Blue:
      _turnOff(_bluePin);
      break;
    case LedColor::Orange:
      _turnOff(_redPin);
      _turnOff(_greenPin);
      break;
    case LedColor::Purple:
      _turnOff(_redPin);
      _turnOff(_bluePin);
      break;
    case LedColor::Cyan:
      _turnOff(_greenPin);
      _turnOff(_bluePin);
      break;
    case LedColor::White:
      _turnOff(_redPin);
      _turnOff(_greenPin);
      _turnOff(_bluePin);
      break;
    default:
      break;
  }
}

void RgbLed::_turnOn(uint8_t pin) {
  digitalWrite(pin, LOW);
}

void RgbLed::_turnOff(uint8_t pin) {
  digitalWrite(pin, HIGH);
}
