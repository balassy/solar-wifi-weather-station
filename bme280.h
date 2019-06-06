#include <Arduino.h>

#ifndef bme280_h
#define bme280_h

// Third-party libraries.
#include <Adafruit_BME280.h>  // Adafruit BME280 Library, depends on Adafruit Unified Sensor library too.

#define SEALEVELPRESSURE_HPA (1013.25)
#define DEFAULT_ADDRESS 0x76

class BME280 {
 public:
  typedef struct {
    float temperature;
    float pressure;
    float altitude;
    float humidity;
  } Measurement;

  void init();
  float getTemperature();
  float getPressure();
  float getAltitude();
  float getHumidity();
  Measurement getMeasuredData();

 private:
  Adafruit_BME280 _bme;
};

#endif /* bme280_h */
