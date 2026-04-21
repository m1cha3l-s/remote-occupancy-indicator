#include <WiFi.h>
#include <Wire.h>
#include <esp_now.h>
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel remote(7, 0, NEO_GRB + NEO_KHZ800);

  //esp-now stuff
uint8_t broadcastAddress[] = {0xA4, 0xCB, 0x8F, 0x1D, 0x52, 0xB8};   //MAC Address format 11:22:33:44:55:66 (MAC of your remote for sending back which color is shown every time it's changed)
#define CHANNEL 0   //channel which esp-now uses

float Indicator_current;

typedef  struct struck_message {
  float set;
  float get;
} struck_message;

struck_message Indicator_data;
struck_message Remote_data;
esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.println("Delivering");
}

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&Indicator_data, incomingData, sizeof(Indicator_data));
  Indicator_current = Indicator_data.get;
  Serial.println("Data recv: ");
  Serial.println(Indicator_data.get);
  remote.fill(Indicator_data.get, 3, 4);
  remote.show();
}

const int aaa = 3;
const int bbb = 2;
const int ccc = 1;

void setup() {
  Serial.begin(115200);

  pinMode(aaa, INPUT_PULLUP);
  pinMode(bbb, INPUT_PULLUP);
  pinMode(ccc, INPUT_PULLUP);

  WiFi.mode(WIFI_STA);

  esp_now_init();
  peerInfo.channel = CHANNEL;
  peerInfo.encrypt = false;

  memcpy(peerInfo.peer_addr, broadcastAddress, 6);

  esp_now_add_peer(&peerInfo);
  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));

  remote.begin();
  remote.fill(0, 3, 4);
  remote.setPixelColor(0, remote.Color(255, 0, 0));
  remote.setPixelColor(1, remote.Color(255, 95, 31));
  remote.setPixelColor(2, remote.Color(0, 255, 0)); 
  remote.show();
}

void loop(){
  if (digitalRead(aaa) == LOW) {
    Remote_data.set = remote.Color(255, 0, 0);
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &Remote_data, sizeof(Remote_data));
    Serial.println("Button 1");
    delay(1200);
  } 
  else if (digitalRead(bbb) == LOW) {
    Remote_data.set = remote.Color(255, 95, 31);
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &Remote_data, sizeof(Remote_data));
    Serial.println("Button 2");
    delay(1200);
  }
  else if (digitalRead(ccc) == LOW) {
    Remote_data.set = remote.Color(0, 255, 0);
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &Remote_data, sizeof(Remote_data));
    Serial.println("Button 3");
    delay(1200);
  }
}