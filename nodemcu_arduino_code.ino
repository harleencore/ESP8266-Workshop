//configuring
#include <ESP8266WiFi.h>  //this is the library you'll need for esp stuff
const short int led = 16; //this is to tell the esp that we have an LED on GPIO16
WiFiServer server(80); //Initialize the server on Port 80 (Global instance)

//setting up
void setup() {
  //boilerplate code
  WiFi.mode(WIFI_AP); //Our ESP8266-12E is an AccessPoint 
  WiFi.softAP("Harleen_server", "mousse"); // Provide the (SSID, password); . 
  server.begin(); // Start the HTTP Server
  
  //peeking under the hood: this is how we know what's going on
  //IMPORTANT: serial output baud rate has to match the one you manually select for your serial monitor
  Serial.begin(9600); //Start communication between the ESP8266-12E and the monitor window
  IPAddress HTTPS_ServerIP= WiFi.softAPIP(); // Obtain the IP of the Server 
  Serial.print("Server IP is: "); // Print the IP to the monitor window 
  Serial.println(HTTPS_ServerIP);
  

  //here we set up the LED
  pinMode(led, OUTPUT); //GPIO16 is an OUTPUT pin;
  digitalWrite(led, LOW); //Initial state is OFF
}

//this code gets run ALWAYS
void loop() {
  
  WiFiClient client = server.available();
  if (!client) { 
    return; //keep searching if server isn't available!!
  } 
  
  //Looking under the hood- so we're kept in the loop (heheh)
  Serial.println("Somebody has connected :)");

  //Read what the browser has sent into a String class and print the request to the monitor
  String request = client.readStringUntil('\r'); 
  //Looking under the hood 
  Serial.println(request);


  //for the LED: if someone tries to do something,
  // Handle the Request
  
  if (request.indexOf("/ON") != -1){ 
  digitalWrite(led, HIGH); }
  else if (request.indexOf("/OFF") != -1){ 
  digitalWrite(led, LOW); 
}

  }

