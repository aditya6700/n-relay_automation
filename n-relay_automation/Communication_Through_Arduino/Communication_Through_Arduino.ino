#include<ArduinoJson.h>

void setup()
{
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
 

  digitalWrite(13,LOW);
  digitalWrite(12,LOW);
  

  Serial.begin(9600);
  }
void loop()
{
  int led;
  int led_status;
  
  DynamicJsonDocument doc(1024);
  
  // Sending the request
  doc["type"] = "request";
  serializeJson(doc,Serial); // { "type" : "request" }
  // Reading the response
  boolean messageReady = false;
  String message = "";
  while(messageReady == false) 
  { // blocking but that's ok
    if(Serial.available()) 
    {
      message = Serial.readString();
      messageReady = true;
    }
  }
  // Attempt to deserialize the JSON-formatted message
  DeserializationError error = deserializeJson(doc,message);
  if(error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    return;
  }
  led = doc["led"];
  led_status = doc["status"];
 
  
  digitalWrite(led,led_status);
  } 
