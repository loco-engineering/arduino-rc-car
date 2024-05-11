#include <esp_now.h>
#include <WiFi.h>

//Replace this address with the address of a car
uint8_t car_address[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

esp_now_peer_info_t car_controller_info;

void i_sent_data_to_car(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Message has been delivered" : "Upps. Cannot deliver a message");
}
 
void setup() {
  Serial.begin(115200);
 
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(i_sent_data_to_car);
  
  memcpy(car_controller_info.peer_addr, car_address, 6);
  car_controller_info.channel = 0;  
  car_controller_info.encrypt = false;
  
  if (esp_now_add_peer(&car_controller_info) != ESP_OK){
    Serial.println("Cannot connect to a car");
    return;
  }
}
 
void loop() {

  int valueX = analogRead(1);
  Serial.println("valueX:");
  Serial.println(valueX);

  int valueY = analogRead(0);
  Serial.println("valueY:");
  Serial.println(valueY);

  uint8_t message[3] = {0};
  message[0] = 2;
  message[1] = valueX/20;
  message[2] = valueY/20;

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(car_address, message, sizeof(message));
   
  if (result == ESP_OK) {
    Serial.println("Message has been sent to a car");
  }
  else {
    Serial.println("Cannot send a message to a car");
  }

  delay(100);
}