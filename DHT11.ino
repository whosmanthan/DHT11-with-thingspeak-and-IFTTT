#include<ESP8266WiFi.h>
#include<ThingSpeak.h>
#include "DHT.h" 
#include <WiFiClientSecure.h>
#include <ESP8266Webhook.h>

#define KEY "XXXXXXXXXXXXXXXX"        // Webhooks Key

// Webhooks Event Name
#define EVENT1 "EVENT 1 EMAIL" 
#define EVENT2 "EVENT 2 SMS"

WiFiClient client;     //define client
//ThingSpeak
long myChannelNumber = ____________;
const char myWriteAPIKey[] = "API KEY";

DHT dht2(15,DHT11);
Webhook webhook1(KEY, EVENT1);    // Create an object.
Webhook webhook2(KEY, EVENT2);    // Create an object.

void setup() {
  Serial.begin(115200);  
  WiFi.begin("realme 6","0987654321");
  while(WiFi.status()!= WL_CONNECTED)
  { //WL_IDLE_STATUS, WL_CONNECT_FAILED
    Serial.print('.');
    delay(200);
  }  
  Serial.println();
  Serial.println("Witty Board connected");
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client);
  }

void loop() {
   float t = dht2.readTemperature();
   float h = dht2.readHumidity();

   String temp = String(t,1);
   String humidity = String(h,0);
   
   Serial.println("Temperature in C:");
   Serial.println((dht2.readTemperature( )));  
   Serial.println("Humidity in C:");  
   Serial.println((dht2.readHumidity()));  

   ThingSpeak.writeField(myChannelNumber, 1, temp, myWriteAPIKey);
   ThingSpeak.writeField(myChannelNumber, 2, humidity, myWriteAPIKey);

 if (t >= 20 && h >= 20) // set threshold
  {
  webhook1.trigger(temp,humidity);
  webhook2.trigger(temp,humidity);
  delay(360000); // 5 min delay for Trigger
  }
  else 
  {
    return;
  }
 delay(1000);
}
