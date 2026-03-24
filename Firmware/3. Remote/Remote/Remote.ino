#include <WiFi.h>
#include <esp_now.h>
#include <Adafruit_NeoPixel.h>


int button1 = 3;
int button2 = 2;
int button3 = 1;

Adafruit_NeoPixel remote(7, 0, NEO_GRB + NEO_KHZ800);

  //esp-now stuff
uint8_t broadcastAddress[] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66};   //MAC Address format 11:22:33:44:55:66 (MAC of your remote for sending back which color is shown every time it's changed)
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
  memcpy(&Indicator_data, incomingData, sizeof(Indicator_data));
  Serial.println("Data recv: ");
  Serial.println(Indicator_data.get);
  remote.fill(Indicator_data.get, 3, 4);
  remote.show();
}

void setup() {
  Serial.begin(115200);

  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);

  WiFi.mode(WIFI_STA);

  esp_now_init();
  peerInfo.channel = CHANNEL;
  peerInfo.encrypt = false;

  esp_now_register_send_cb(OnDataSent);
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
  if (digitalRead(button1) == LOW) {
    Remote_data.set = remote.Color(255, 0, 0);
    esp_now_send(broadcastAddress, (uint8_t *) &Remote_data, sizeof(Remote_data));
    delay(1200);
  } 
  else if (digitalRead(button2) == LOW) {
    Remote_data.set = remote.Color(255, 95, 31);
    esp_now_send(broadcastAddress, (uint8_t *) &Remote_data, sizeof(Remote_data));
    delay(1200);
  }
  else if (digitalRead(button3) == LOW) {
    Remote_data.set = remote.Color(0, 255, 0);
    esp_now_send(broadcastAddress, (uint8_t *) &Remote_data, sizeof(Remote_data));
    delay(1200);
  }
}