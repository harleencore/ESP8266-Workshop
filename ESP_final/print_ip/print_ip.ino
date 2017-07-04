#include <ESP8266WiFi.h>

//WiFi parameters to be configured:
const char* ssid = "SIDHU Family-5GHz";
const char* password = "81332664";

void setup() {
  Serial.begin(9600);
  //Connect to WiFi
  WiFi.begin(ssid, password);

  //while wifi not conencted yet, print ','
  //after connected, get out of loop
  while(WiFi.status()!= WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  
  //print a new line, then tell you it's conencted + IP address
  Serial.println("");
  Serial.println("WiFi connected");
  //print the IP address
  Serial.print(WiFi.localIP());

}

void loop() {
  // nada

}
