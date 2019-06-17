// Platform libraries.
#include <Arduino.h>           // To add IntelliSense for platform constants.
#include <ESP8266WiFi.h>       // To connect to the WiFi network.

// Third-party libraries.
#include <WiFiManager.h>  // To manage network configuration and connection.

// My classes.
#include "bme280.h"              // To read the temperature, pressure and humidity sensor.
#include "ifttt-client.h"        // To manage the communication with the IFTTT service.
#include "magicmirror-client.h"  // To manage the communication with the MagicMirror.
#include "status-led.h"          // To control the status LED.
#include "thingspeak-client.h"   // To send measured data to the ThingSpeak service.
#include "blynk-client.h"        // To send measured data to the Blynk service.
// #include "ota-updater.h"         // To manage over-the-air updates of new code.

#include "config.h"  // To store configuration and secrets.

WiFiManager wifiManager;
BME280 bme;

MagicMirrorClient magicMirror;
IftttClient ifttt;
ThingSpeakClient thingSpeak;
BlynkClient blynk;
StatusLed led;
// OTAUpdater updater;

void setup() {
  initSerial();
  initLed();
  led.onBootStarted();

  initNetwork();
  initMagicMirrorClient();
  initIftttClient();
  initThingSpeakClient();
  initBlynkClient();
  initTemperatureSensor();
//  initUpdater();

  sendStartNotification();

  led.onBootEnded();
  Serial.printf("Application version: %s\n", APP_VERSION);
  Serial.println("Setup completed.");

  measureAndUpdateTargets();

  goToDeepSleep();
}

void loop() {
  // No code here, because all logic is running in the setup phase and then the device goes to deep sleep.
  // After waking up the setup phase is executed again.
}

void initSerial() {
  Serial.begin(74880); // 74880 is the speed used to print boot messages.
  Serial.println();
  Serial.println("Initializing serial connection DONE.");
}

void initLed() {
  Serial.printf("Initializing RGB LED on pins %d, %d, %d...", PIN_LED_RED, PIN_LED_GREEN, PIN_LED_BLUE);
  led.setPins(PIN_LED_RED, PIN_LED_GREEN, PIN_LED_BLUE);
  Serial.println("DONE.");
}

void initNetwork() {
  Serial.printf("Initializing connection to the network with MAC address %s using WiFiManager (SSID: %s)...\n", WiFi.macAddress().c_str(), WIFI_AP_SSID);
  wifiManager.setAPCallback([&](WiFiManager *mgr) {
    led.onWifiManagerAccessPointModeStarted();
  });
  wifiManager.setSaveConfigCallback([&]() {
    led.onWifiManagerAccessPointModeEnded();
  });

  wifiManager.setConfigPortalTimeout(WIFI_CONFIG_PORTAL_TIMEOUT_SECONDS);

  if (!wifiManager.autoConnect(WIFI_AP_SSID, WIFI_AP_PASSWORD)) {
    Serial.println("Failed to connect to the network and the WiFi configuration portal hit inactivity timeout. Restarting the device in 3 seconds and trying again...");
    delay(3000);
    ESP.restart();
  }

  Serial.printf("DONE. IP address: %s, MAC address: %s\n", WiFi.localIP().toString().c_str(), WiFi.macAddress().c_str());
}

void initMagicMirrorClient() {
  Serial.printf("Initializing MagicMirror client to host %s...", MAGIC_MIRROR_HOST);
  magicMirror.setHostUrl(MAGIC_MIRROR_HOST);
  Serial.println("DONE.");
}

void initIftttClient() {
  Serial.print("Initializing IFTTT client...");
  ifttt.setApiKey(IFTTT_WEBHOOK_API_KEY);

  String deviceName = String(OTA_UPDATE_HOSTNAME) + " (Version: " + APP_VERSION + ", IP: " + WiFi.localIP().toString() + ", MAC: " + WiFi.macAddress() + ")";
  ifttt.setDeviceName(deviceName);

  Serial.println("DONE.");
}

void initThingSpeakClient() {
  Serial.print("Initializing ThingSpeak client...");
  thingSpeak.setApiKey(THINGSPEAK_API_KEY);
  Serial.println("DONE.");
}

void initBlynkClient() {
  Serial.print("Initializing Blynk client...");
  blynk.setAuthToken(BLYNK_AUTH_TOKEN);
  blynk.waitUntilConnected();
  Serial.println("DONE.");
}

void initTemperatureSensor() {
  Serial.print("Initializing the temperature sensor...");
  bme.init();
  Serial.println("DONE.");
}

// void initUpdater() {
//   Serial.print("Initializing over-the-air updater...");
//   updater.initialize(OTA_UPDATE_HOSTNAME, OTA_UPDATE_PASSWORD, ifttt, led);
//   Serial.println("DONE.");
// }

void sendStartNotification() {
  // Send start notification only if the device has not waken up from deep sleep,
  // so the start happened unexpectedly.

  String resetReason = ESP.getResetReason();
  Serial.println("Reset reason: " + resetReason);

  if (resetReason != "Deep-Sleep Wake") {
    Serial.println("Sending notification about unexpected start...");
    String message = String("Your device is starting. Reason: ") +  resetReason + " (" + ESP.getResetInfo() + ")";
    ifttt.triggerEvent(IFTTT_WEBHOOK_EVENT_NAME, "Starting", message);
    Serial.println("DONE.");
  }
}

void measureAndUpdateTargets() {
  Serial.println("Measuring...");
  led.onMeasurementStarted();
  
  Serial.print("Reading sensor data...");
  BME280::Measurement m = bme.getMeasuredData();
  Serial.println(" DONE.");

  Serial.printf("Temperature: %.1f °C\n", m.temperature);
  Serial.printf("Pressure: %.1f hPa\n", m.pressure);
  Serial.printf("Altitude: %.1f m\n", m.altitude);
  Serial.printf("Humidity: %.1f %%\n", m.humidity);

  Serial.print("Reading battery voltage... ");
  float voltage = readBatteryVoltage();
  Serial.print(voltage);
  Serial.println("V DONE.");

  Serial.println("Sending data to ThingSpeak...");
  thingSpeak.writeField(String(m.temperature), String(m.humidity), String(voltage), "");
  Serial.println("DONE.");

  Serial.println("Sending data to MagicMirror...");
  magicMirror.sendTemperature(m.temperature, m.humidity);
  Serial.println("DONE.");

  Serial.print("Sending data to Blynk...");
  blynk.sendUpdate(m.temperature, m.humidity, voltage);
  Serial.println("DONE.");

  led.onMeasurementEnded();
  Serial.println("Measuring: DONE.");
}

float readBatteryVoltage() {
  // Voltage divider R1 = 220k+100k+220k =540k and R2=100k
  float calib_factor = 5.28; // change this value to calibrate the battery voltage
  unsigned long raw = analogRead(A0);
  float volt = raw * calib_factor/1024; 
  return volt;
}

void goToDeepSleep() {
  Serial.printf("Going to sleep for %.0f seconds...\n", UPDATE_INTERVAL_SECONDS);
  pinMode(D0, WAKEUP_PULLUP);
  ESP.deepSleep(UPDATE_INTERVAL_SECONDS * 1e6); // Microseconds.
  delay(10);
}
