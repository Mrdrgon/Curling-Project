#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "WiFi.h"
#include <esp_now.h>
#include <Bounce2.h> 
uint8_t code = 0x90;
Bounce2::Button button1 = Bounce2::Button();
Bounce2::Button button2 = Bounce2::Button();
Bounce2::Button button3 = Bounce2::Button();
Bounce2::Button button4 = Bounce2::Button(); // INSTANTIATE A Bounce2::Button OBJECT
typedef struct {uint8_t code; uint8_t message;} esp_payload;

// put function declarations here:
//int positionToLED(int);
//Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

esp_now_peer_info_t peerInfo;
uint8_t broadcastAddress[] = {0xD4, 0xE9, 0xF4, 0xC3, 0x0C, 0xEC};
//uint8_t broadcastAddress[] = {0xD4, 0xE9, 0xF4, 0xC3, 0x73, 0x98};
typedef struct
{
  uint8_t buttonNum;
}ButtonPress;
int currStateLeft = 0; // 0 = stop 1 = clean 2 = left 3= right
int currStateRight = 0; 
int currSide = 0; //0=left 1 = right
ButtonPress msg;

void OnDataSent(const wifi_tx_info_t *macadresss, esp_now_send_status_t status)
{
  //Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);

  // pinMode(Button_PIN,INPUT_PULLUP);
  // pinMode(Button_PIN,INPUT_PULLUP);
  // pinMode(Button_PIN,INPUT_PULLUP);
  // pinMode(Button_PIN,INPUT_PULLUP);
   //strip.clear();
  
  //strip.setPixelColor(1, 255, 0, 255);
  //strip.show();

  button1.attach ( 13 , INPUT_PULLUP );
  button1.interval(5);
  button1.setPressedState(LOW); 

  button2.attach ( 12 , INPUT_PULLUP );
  button2.interval(5);
  button2.setPressedState(LOW); 

  button3.attach ( 14 , INPUT_PULLUP );
  button3.interval(5);
  button3.setPressedState(LOW); 

  button4.attach ( 27 , INPUT_PULLUP );
  button4.interval(5);
  button4.setPressedState(LOW); 

  WiFi.mode(WIFI_MODE_STA);
  //WiFi.begin();
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_send_cb(OnDataSent);

  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    Serial.println("Failed to add peer");
    return;
  }

  //pinMode(LED_PIN,OUTPUT);
  //digitalWrite(LED_PIN,LOW);

}


void loop()
{
  // put your main code here, to run repeatedly:

  button1.update();
  button2.update();
  button3.update();
  button4.update();
  int state;
    if ( button1.pressed() ) {
    //digitalWrite(LED_PIN,HIGH);
    Serial.println("Stop");
    state = 0;
  }else if (button2.pressed()){
    //digitalWrite(LED_PIN,HIGH);
    Serial.println("Clean");
    state = 1;
  }else if (button3.pressed()){
    //digitalWrite(LED_PIN,HIGH);
    Serial.println("Sweep Left");
    state = 2;
  }else if (button4.pressed()){
    //digitalWrite(LED_PIN,HIGH);
    Serial.println("Sweep Right");
    state = 3;
  }

  
  esp_payload payload = {code, state};
  
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &payload, sizeof(esp_payload));
   
  if (result == ESP_OK) {
    Serial.println("Sending confirmed");
  }
  else {
    Serial.println("Sending error");
  }
}
//0=stop 1=clean 2 = left 3= right 4 = both


int currState = 0; //0=stop 1=clean 2 = sweep
int currSide = 0; //0=left 1 = right
int changeState(int message) {
  if (message == 0) { //stop
    currState = 0;
    Serial.println("Stop");
  }
  else if (message == 1) {  //clean
    currState = 1;
    Serial.println("Clean");
  }
  else if (message == 2) { //left
    
    if (currState == 2) {
      currState = 0;
    } 
    else if (currState == 0) {
      currState = 2;
    }
    else if (currState == 3) {
      currState = 
    }
    
    Serial.println("Sweeping");
    
    
  }
  else if (message == 3) { //right
    if (currSide == 1) {
      toggleState(currState);
      Serial.println("Sweeping");
    }
    
  }
}

int toggleState(int state) {
  if (state == 2) {
    return 0;
  }
  return 2;
}

//