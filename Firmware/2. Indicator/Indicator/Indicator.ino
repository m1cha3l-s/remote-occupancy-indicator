#include <WiFi.h>
#include <esp_now.h>
#include <Adafruit_NeoPixel.h>

  //set pins and number of leds for neopixel
Adafruit_NeoPixel indicator(9, 3, NEO_GRB + NEO_KHZ800);

  //esp-now stuff
uint8_t broadcastAddress[] = {0xC8, 0xC9, 0xA3, 0xC7, 0xFC, 0xB0};   //MAC Address format 11:22:33:44:55:66 (MAC of your remote for sending back which color is shown every time it's changed)
#define CHANNEL 0   //channel which esp-now uses

typedef  struct struck_message {
  uint32_t set;
  uint32_t get;
} struck_message;

struck_message Indicator_data;
struck_message Remote_data;
esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.println("Delivering");
}

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&Remote_data, incomingData, sizeof(Remote_data));
  Serial.println("Data recv: ");
  Serial.println(Remote_data.set);
  indicator.fill(Remote_data.set, 0, 9);
  indicator.show();
  uint32_t currentColor = indicator.getPixelColor(0);
  Indicator_data.get = currentColor;
  esp_now_send(broadcastAddress, (uint8_t *) &Indicator_data, sizeof(Indicator_data));
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