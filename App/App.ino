#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <functional>
#include "switch.h"
#include "UpnpBroadcastResponder.h"
#include "CallbackFunction.h"

// prototypes
boolean connectWifi();

// on/off callbacks

bool roomLightOneON();
bool roomLightOneOFF();
bool roomLightTwoON();
bool roomLightTwoOFF();
bool roomFanON();
bool roomFanOFF();
bool roomOutFanON();
bool roomOutFanOFF();
bool hallLightON();
bool hallLightOFF();
bool hallFanON();
bool hallFanOFF();
bool hallTvON();
bool hallTvOFF();
bool sitOutLightON();
bool sitOutLightOFF();

// Change this before you flash
const char *ssid = "MY_LAN";
const char *password = "PtsLANpassword";

boolean wifiConnected = false;

UpnpBroadcastResponder upnpBroadcastResponder;
 

Switch *roomLightOne = NULL;
Switch *roomLightTwo = NULL;
Switch *roomFan = NULL;
Switch *roomOutFan = NULL;

Switch *hallLight = NULL;
Switch *hallFan = NULL;
Switch *hallTv = NULL;

Switch *sitOutLight = NULL;

//relay pin setup for funct
int relayOne = 5;
int relayTwo = 4;
int relayThree = 0;
int relayFour = 2;
int relayFive = 14;
int relaySix = 12;
int relaySeven = 13;
int relayEight = 15;

void setup()
{
     Serial.begin(9600);

     // Initialise wifi connection
     wifiConnected = connectWifi();

     if (wifiConnected)
     {
          upnpBroadcastResponder.beginUdpMulticast();

          // Define your switches here. Max 10
          // Format: Alexa invocation name, local port no, on callback, off callback

          roomLightOne = new Switch("Room Light", 80, roomLightOneON, roomLightOneOFF);
          roomLightTwo = new Switch("Room Light Two", 81, roomLightTwoON, roomLightTwoOFF);
          roomFan = new Switch("Room Fan", 82, roomFanON, roomFanOFF);
          roomOutFan = new Switch("Room Outfan", 83, roomOutFanON, roomOutFanOFF);

          hallLight = new Switch("Hall light", 84, hallLightON, hallLightOFF);
          hallFan = new Switch("Hall fan", 85, hallFanON, hallFanOFF);
          hallTv = new Switch("Tv", 86, hallTvON, hallTvOFF);

          sitOutLight = new Switch("Sit out light", 87, sitOutLightON, sitOutLightOFF);

          upnpBroadcastResponder.addDevice(*roomLightOne);
          upnpBroadcastResponder.addDevice(*roomLightTwo);
          upnpBroadcastResponder.addDevice(*roomFan);
          upnpBroadcastResponder.addDevice(*roomOutFan);

          upnpBroadcastResponder.addDevice(*hallLight);
          upnpBroadcastResponder.addDevice(*hallFan);
          upnpBroadcastResponder.addDevice(*hallTv);

          upnpBroadcastResponder.addDevice(*sitOutLight);

          //relay pins setup i Used D1,D2,D3,D4,D5,D6,D7,D8 followed as assigned below, 
          //if you are willing to change Pin or planning to use extra please Check Image in Github File..:)
          pinMode(5, OUTPUT);
          pinMode(4, OUTPUT);
          pinMode(0, OUTPUT);
          pinMode(2, OUTPUT);

          pinMode(14, OUTPUT);
          pinMode(12, OUTPUT);
          pinMode(13, OUTPUT);

          pinMode(15, OUTPUT);

          digitalWrite(5, HIGH);
          digitalWrite(4, HIGH);
          digitalWrite(0, HIGH);
          digitalWrite(2, HIGH);

          digitalWrite(14, HIGH);
          digitalWrite(12, HIGH);
          digitalWrite(13, HIGH);

          digitalWrite(15, HIGH);
     }
}

void loop()
{
     if (wifiConnected)
     {
          upnpBroadcastResponder.serverLoop();

          roomLightOne->serverLoop();
          roomLightTwo->serverLoop();
          roomFan->serverLoop();
          roomOutFan->serverLoop();

          hallLight->serverLoop();
          hallFan->serverLoop();
          hallTv->serverLoop();

          sitOutLight->serverLoop();
     }
}
// connect to wifi – returns true if successful or false if not
boolean connectWifi()
{
     boolean state = true;
     int i = 0;

     WiFi.mode(WIFI_STA);
     WiFi.begin(ssid, password);
     Serial.println("");
     Serial.println("Connecting to WiFi");

     // Wait for connection
     Serial.print("Connecting ...");
     while (WiFi.status() != WL_CONNECTED)
     {
          delay(500);
          Serial.print(".");
          if (i > 10)
          {
               state = false;
               break;
          }
          i++;
     }

     if (state)
     {
          Serial.println("");
          Serial.print("Connected to ");
          Serial.println(ssid);
          Serial.print("IP address: ");
          Serial.println(WiFi.localIP());
     }
     else
     {
          Serial.println("");
          Serial.println("Connection failed.");
     }

     return state;
}

/**
 *  It will trigger when Alexa call 
 */
bool roomLightOneON()
{
     digitalWrite(relayOne, LOW); // sets relayOne on
     return true;
}
bool roomLightOneOFF()
{
     digitalWrite(relayOne, HIGH); // sets relayOne off
     return true;
}
bool roomLightTwoON()
{
     digitalWrite(relayTwo, LOW); // sets relayTwo on
     return true;
}
bool roomLightTwoOFF()
{
     digitalWrite(relayTwo, HIGH); // sets relayTwo off
     return true;
}
bool roomFanON()
{
     digitalWrite(relayThree, LOW); // sets relayThree on
     return true;
}
bool roomFanOFF()
{
     digitalWrite(relayThree, HIGH); // sets relayThree off
     return true;
}
bool roomOutFanON()
{
     digitalWrite(relayFour, LOW); // sets relayFour on
     return true;
}
bool roomOutFanOFF()
{
     digitalWrite(relayFour, HIGH); // sets relayFour off
     return true;
}

bool hallLightON()
{
     digitalWrite(relayFive, LOW); // sets relayFive on
     return true;
}
bool hallLightOFF()
{
     digitalWrite(relayFive, HIGH); // sets relayFive off
     return true;
}
bool hallFanON()
{
     digitalWrite(relaySix, LOW); // sets relaySix on
     return true;
}
bool hallFanOFF()
{
     digitalWrite(relaySix, HIGH); // sets relaySix off
     return true;
}
bool hallTvON()
{
     digitalWrite(relaySeven, LOW); // sets relaySeven on
     return true;
}
bool hallTvOFF()
{
     digitalWrite(relaySeven, HIGH); // sets relaySeven off
     return true;
}
bool sitOutLightON()
{
     digitalWrite(relayEight, LOW); // sets relayEight on
     return true;
}
bool sitOutLightOFF()
{
     digitalWrite(relayEight, HIGH); // sets relayEight off
     return true;
}
