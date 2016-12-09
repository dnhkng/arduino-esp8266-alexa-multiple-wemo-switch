#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <functional>
#include "switch.h"
#include "UpnpBroadcastResponder.h"
#include "CallbackFunction.h"
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

// prototypes
boolean connectWifi();

//on/off callbacks 
void aLightsOn();
void aLightsOff();
void bLightsOn();
void bLightsOff();
void cLightsOn();
void cLightsOff();
void dLightsOn();
void dLightsOff();
void dLightsOn();
void dLightsOff();

// Change this before you flash
const char* ssid = "nanoguest";
const char* password = "WelcomeToNTT";

boolean wifiConnected = false;

UpnpBroadcastResponder upnpBroadcastResponder;

Switch *aSwitch = NULL;
Switch *bSwitch = NULL;
Switch *cSwitch = NULL;
Switch *dSwitch = NULL;
Switch *eSwitch = NULL;

void setup()
{
  Serial.begin(9600);
  delay(1000);
  Serial.println("Adding switches upnp broadcast responder"); 
  // Initialise wifi connection
  wifiConnected = connectWifi();
  
  if(wifiConnected){
    mySwitch.enableTransmit(2);
    mySwitch.setPulseLength(170);
    mySwitch.setRepeatTransmit(5);
    
    upnpBroadcastResponder.beginUdpMulticast();
    
    // Define your switches here. Max 14
    // Format: Alexa invocation name, local port no, on callback, off callback
    
    aSwitch = new Switch("christmas lights", 80, aLightsOn, aLightsOff);
    bSwitch = new Switch("coffee machine", 81, bLightsOn, bLightsOff);
    cSwitch = new Switch("speaker", 82, cLightsOn, cLightsOff);
    dSwitch = new Switch("lounge room light", 83, dLightsOn, dLightsOff);
    eSwitch = new Switch("kettle", 84, eLightsOn, eLightsOff);

    Serial.println("Adding switches upnp broadcast responder");
    upnpBroadcastResponder.addDevice(*aSwitch);
    upnpBroadcastResponder.addDevice(*bSwitch);
    upnpBroadcastResponder.addDevice(*cSwitch);
    upnpBroadcastResponder.addDevice(*dSwitch);
    upnpBroadcastResponder.addDevice(*eSwitch);
  }
}
 
void loop()
{
	 if(wifiConnected){
      upnpBroadcastResponder.serverLoop();
      
      aSwitch->serverLoop();
      bSwitch->serverLoop();
      cSwitch->serverLoop();
      dSwitch->serverLoop();
      eSwitch->serverLoop();
	 }
}

void aLightsOn() {
    Serial.print("Switch a turn on ...");
    mySwitch.send("010000000001010100110011");
}

void aLightsOff() {
    Serial.print("Switch a turn off ...");
    mySwitch.send("010000000001010100111100");
}

void bLightsOn() {
    Serial.print("Switch b turn on ...");
    mySwitch.send("010000000001010111000011");
}

void bLightsOff() {
  Serial.print("Switch b turn off ...");
   mySwitch.send("010000000001010111001100");
}

void cLightsOn() {
    Serial.print("Switch c turn on ...");
    mySwitch.send("010000000001011100000011");
}

void cLightsOff() {
    Serial.print("Switch c turn off ...");
    mySwitch.send("010000000001011100001100");
}

void dLightsOn() {
    Serial.print("Switch d turn on ...");
    mySwitch.send("010000000001110100000011");
}

void dLightsOff() {
  Serial.print("Switch d turn off ...");
  mySwitch.send("010000000001110100001100");
}

void eLightsOn() {
    Serial.print("Switch e turn on ...");
    mySwitch.send("010000000011010100000011");
}

void eLightsOff() {
    Serial.print("Switch e turn off ...");
    mySwitch.send("010000000011010100001100");
}


// connect to wifi – returns true if successful or false if not
boolean connectWifi(){
  boolean state = true;
  int i = 0;
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting ...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 10){
      state = false;
      break;
    }
    i++;
  }
  
  if (state){
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("");
    Serial.println("Connection failed.");
  }
  
  return state;
}
