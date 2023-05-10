// ===========================
// Includes for ESP32 camera webserver
// ===========================
#include "esp_camera.h"
#include <WiFi.h>
#define CAMERA_MODEL_AI_THINKER
#include "camera_pins.h"

// ===========================
// Hotspot connection information
// ===========================
const char* ssid = "Kory";
const char* password = "12345678";

// ===========================
// IP address and port for TCP and ICP
// ===========================
const uint16_t port = 8091;
const char * host = "172.20.10.3";

// ===========================
// Definiations for States
// ===========================
// the number of the pwm pin
//const int pwmPinH = 2;  // 2 corresponds to GPIO2
//int stateOff;
//int stateLow;
//int stateHigh;
const int bagswitch = 14;
int stateBag;
const int magnetpin = 2;
//#define Off 15 // 15 corresponds to GPIO15
//#define Low 13 // 13 corresponds to GPIO13
//#define High 12  // 12 corresponds to GPIO12
//#define Panel 14 //14 corresponds to GPIO14

// ===========================
// Start the Camera's Webserver
// ===========================
void startCameraServer();
void setupLedFlash(int pin);

void setup()
{
 
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();

  pinMode(bagswitch, INPUT_PULLUP);
  pinMode(magnetpin, OUTPUT); //15? we could also try 14 or IO14
  // configure LED PWM functionalitites
  //ledcSetup(pwmChannelL, freq, resolution);
  //ledcSetup(pwmChannelH, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  //ledcAttachPin(pwmPinL, pwmChannelL);
  //ledcAttachPin(pwmPinH, pwmChannelH);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }
 
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  //config.frame_size = FRAMESIZE_UXGA;
  config.pixel_format = PIXFORMAT_JPEG; // for streaming
  //config.pixel_format = PIXFORMAT_RGB565; // for face detection/recognition
  //config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;
  //config.fb_location = CAMERA_FB_IN_PSRAM;
  //config.jpeg_quality = 12;
  //config.fb_count = 1;
  
  if(psramFound()){
    config.frame_size = FRAMESIZE_HD; // FRAMESIZE_ + QVGA|CIF|VGA|SVGA|XGA|SXGA|UXGA
    config.jpeg_quality = 10; //10-63 lower number means higher quality
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_HD;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }
  // drop down frame size for higher initial frame rate
  //if(config.pixel_format == PIXFORMAT_JPEG){
  //  s->set_framesize(s, FRAMESIZE_HD);
  //  s->set_vflip(s, 1);
  //}

// Setup LED FLash if LED pin is defined in camera_pins.h
#if defined(LED_GPIO_NUM)
  setupLedFlash(LED_GPIO_NUM);
#endif

  WiFi.begin(ssid, password);
  WiFi.setSleep(false);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  startCameraServer();

  Serial.print("Camera Ready! Use 'http://");
  Serial.print(WiFi.localIP());
  Serial.println("' to connect");
 
}
 
void loop()
{
    int dutyHigh = 255; //pwm voltage high setting
    int dutyOff = 0; //pwm voltage off setting

    WiFiClient client;
    String string;
 
    if (!client.connect(host, port)) {
 
        Serial.println("Connection to host failed");
 
        delay(1000);
        return;
    }
 
    Serial.println("Connected to server successful!");
    client.print("ESP32 Connected\n");
    
    while (client.connected()) {
      if(client.available() > 0) {
      string = client.readString();
      Serial.println(string);
      }
      Serial.println("Loop");
      //Here we can put all the commands as different strings: if string do this etc
        //High Mode
      if (string=="on"){
        //ledcWrite(pwmChannelL,dutyOff);
        Serial.println("string == on\n");
        //ledcWrite(pwmChannelH,dutyHigh);
        digitalWrite(magnetpin, HIGH);
          }
      //Off Mode
      if (string == "off") {
        Serial.println("string == off\n");
        //ledcWrite(pwmChannelH,dutyOff);
        digitalWrite(magnetpin, LOW);
        //ledcWrite(pwmChannelL,dutyOff);
      }
      //Bag Recognition Switch
      stateBag = digitalRead(bagswitch);
      if (stateBag == LOW) {
        Serial.println("Bag Mounted");
      } else {
        Serial.println("Bag Not Mounted");
      }
      
      if(string == "dis") {
        Serial.println("Disconnecting...");
        client.stop();
      }
      delay(500);
    } 
    delay(10000);
}

  
  
 