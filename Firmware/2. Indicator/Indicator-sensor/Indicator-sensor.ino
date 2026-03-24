#include <WiFi.h>
#include <Wire.h>
#include <esp_now.h>
#include <Adafruit_NeoPixel.h>

  //set pins and number of leds for neopixel
Adafruit_NeoPixel indicator(9, 3, NEO_GRB + NEO_KHZ800);

  //esp-now stuff
uint8_t broadcastAddress[] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66};   //MAC Address format 11:22:33:44:55:66 (MAC of your sensor for sending back which color is shown every time it's changed)
#define CHANNEL 0   //channel which esp-now uses

float Sensor_set;

typedef  struct struck_message {
  float set;
  float get;
} struck_message;

struck_message Indicator_data;
struck_message Sensor_data;
esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.println("Delivering");
}

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&Sensor_data, incomingData, sizeof(Sensor_data));
  Sensor_set = Sensor_data.set;
  Serial.println("Data recv: ");
  Serial.println(Sensor_data.set);
  indicator.fill(Sensor_data.set, 0, 9);
  indicator.show();
  uint32_t currentColor = indicator.getPixelColor(0);
  Indicator_data.get = currentColor;
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &Indicator_data, sizeof(Indicator_data));
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  esp_now_init();
  peerInfo.channel = CHANNEL;
  peerInfo.encrypt = false;

  esp_now_register_send_cb(OnDataSent);
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);

  esp_now_add_peer(&peerInfo);
  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));

  indicator.begin();
  indicator.fill(0, 0, 9);
  indicator.show();
}

void loop(){}