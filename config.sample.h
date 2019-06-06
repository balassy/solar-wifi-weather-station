const char* APP_VERSION = "0.0.1";

const int PIN_LED_RED = 5;              // The number of the GPIO pin where the red cathode (-) of the RGB LED is connected. (5 = D1)
const int PIN_LED_GREEN = 4;            // The number of the GPIO pin where the green cathode (-) of the RGB LED is connected. (4 = D2)
const int PIN_LED_BLUE = 0;             // The number of the GPIO pin where the blue cathode (-) of the RGB LED is connected. (0 = D3)
const int PIN_TEMPERATURE_SENSOR = 14;  // The number of the GPIO pin where the DHT22 sensor is connected. (14 = D5)

const char* WIFI_AP_SSID = "TODO_THERMO_AP";            // The name of the wireless network to create if cannot connect using the previously saved credentials.
const char* WIFI_AP_PASSWORD = "TODO_THERMO_PASSWORD";  // The password required to connect to the wireless network used to configure the network parameters.

const char* OTA_UPDATE_HOSTNAME = "SmarTherm";           // The name of the device as it should appear in the updater tool (e.g. Arduino IDE).
const char* OTA_UPDATE_PASSWORD = "TODO_MY_OTA_SECRET";  // The password that must be sent to the device to accept the update request.

const char* IFTTT_WEBHOOK_EVENT_NAME = "smartherm";           // The name of the IFTTT event to trigger when something important happens with your device.
const char* IFTTT_WEBHOOK_API_KEY = "TODO_MY_IFTTT_API_KEY";  // The IFTTT API key used to trigger the above event.

const char* MAGIC_MIRROR_HOST = "http://192.168.0.123:8080";  // The IP address and port number of the MagicMirror device on the network.

const char* THINGSPEAK_API_KEY = "TODO_MY_THINGSPEAK_API_KEY";  // The API key with write permission to post data to a ThingSpeak channel.

const char* BLYNK_AUTH_TOKEN = "TODO_MY_BLYNK_API_KEY";  // The authentication token to post data to a Blynk project.

float UPDATE_INTERVAL_SECONDS = 60;  // The frequency of measuring data and sending updates to MagicMirror, ThingSpeak and Blynk in seconds.
