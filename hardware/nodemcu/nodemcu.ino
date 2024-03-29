#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

const char* ssid = "innovate";
const char* password = "innovate";

String serverName = "http://137.184.232.255/water_quality_monitoring/data.php";

void setup() {
  Serial.begin(9600); 

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {
  // Send an HTTP POST request depending on timerDelay
  if (Serial.available( ) > 0) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
      String data = Serial.readStringUntil('\n');
      DynamicJsonBuffer jsonBuffer;
      JsonObject& root = jsonBuffer.parseObject(data);
      String temp = root["temp"];
      String ppm = root["ppm"];
      String serverPath = serverName + "?temp=" + temp + "&ppm=" + ppm;
      Serial.println(serverPath);
      http.begin(client, serverPath);
  
      // If you need Node-RED/server authentication, insert user and password below
      //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
        
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
  }
}