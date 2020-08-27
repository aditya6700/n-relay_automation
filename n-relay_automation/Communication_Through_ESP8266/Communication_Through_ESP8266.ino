#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ArduinoJson.h>
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "DCqZVRoRbHcsl5k3jEKWAJlIZlrfucXO";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Area 51";
char pass[] = "WF647241BB1";

int pin;
int pin_status;

BLYNK_WRITE(V2)
{
  pin = 12;
  pin_status = param.asInt();
}

BLYNK_WRITE(V3)
{
  pin = 13;
  pin_status = param.asInt();
}

 

BLYNK_WRITE(V32)
{
  pin = 53;
  pin_status = param.asInt();
}


String message = "";
bool messageReady = false;

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  while(Serial.available()) 
  {
    message = Serial.readString();
    messageReady = true;
  }
  
  // Only process message if there's one
  if(messageReady) 
  {
    // The only messages we'll parse will be formatted in JSON
    DynamicJsonDocument doc(1024); // ArduinoJson version 6+
    // Attempt to deserialize the message
    DeserializationError error = deserializeJson(doc,message);
    if(error) 
    {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      messageReady = false;
      return;
    }
    
    if(doc["type"] == "request") 
    {
      doc["type"] = "response";
      // Get data from virtual pin
      doc["led"] = pin;
      doc["status"] = pin_status;
      
      serializeJson(doc,Serial);  
//       {
//        "type":"response",
//        "led":N,
//        "status": 1/0 
//        }  
    }
    messageReady = false;
  Blynk.run();
}
}
