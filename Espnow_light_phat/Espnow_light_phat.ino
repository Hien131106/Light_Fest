
#include <esp_now.h>
#include <WiFi.h>
byte receiverAddress[] = {0xd0, 0xef, 0x76, 0x5b, 0xa9, 0xa8};  // Địa chỉ MAC của ESP32 nhận

typedef struct struct_message {
    int buttonState;
    int buttonState_2;
    int buttonState_3;
    int buttonState_4;
} struct_message;

struct_message controlData;
const int buttonPin = 4;     // the number of the pushbutton pin
const int buttonPin_2 = 18;
const int buttonPin_3 = 21;
const int buttonPin_4 = 22;
 //Variables will change:

int buttonState = 1;
int buttonState_2 = 1;
int buttonState_3 = 1;
int buttonState_4 = 1;
void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA); //Cho phép esp này kết nối với esp thu
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPin_2, INPUT_PULLUP); 
  pinMode(buttonPin_3, INPUT_PULLUP); 
  pinMode(buttonPin_4, INPUT_PULLUP); 

   if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return; // Thoát nếu có lỗi
    }

  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, receiverAddress, 6);
  //receiverAddress: mảng có kích thước 6 byte chứa địa chỉ của Esp thu 
  //Hàm memcpy: sao chép 6 byte của mảng receiverAddress 
  peerInfo.channel = 0; //Đặt kênh là 0 để 
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return; // Thoát nếu có lỗi
    }
}

void loop() {
      buttonState = digitalRead(buttonPin);
      buttonState_2 = digitalRead(buttonPin_2);
      buttonState_3 = digitalRead(buttonPin_3);
      buttonState_4 = digitalRead(buttonPin_4);
  
  controlData.buttonState = buttonState;
  controlData.buttonState_2 = buttonState_2;
  controlData.buttonState_3 = buttonState_3;
  controlData.buttonState_4 = buttonState_4;

    // Gửi dữ liệu điều khiển đến ESP32 nhận
    esp_now_send(receiverAddress, (uint8_t *) &controlData, sizeof(controlData));
  }



