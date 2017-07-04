//configuring
#include <ESP8266WiFi.h>  //this is the library you'll need for esp stuff
WiFiServer server(80); //Initialize the server on Port 80 (Global instance)
int redPin = 0;
int greenPin = 12;
int bluePin = 15;
#define COMMON_ANODE

//setting up
void setup() {
  //boilerplate code
  WiFi.mode(WIFI_AP); //Our ESP8266-12E is an AccessPoint 
  WiFi.softAP("Hello_IOT", "123456789"); // Provide the (SSID, password); . 
  server.begin(); // Start the HTTP Server
  
  //peeking under the hood: this is how we know what's going on
  //IMPORTANT: serial output baud rate has to match the one you manually select for your serial monitor
  Serial.begin(9600); //Start communication between the ESP8266-12E and the monitor window
  IPAddress HTTPS_ServerIP= WiFi.softAPIP(); // Obtain the IP of the Server 
  Serial.print("Server IP is: "); // Print the IP to the monitor window 
  Serial.println(HTTPS_ServerIP);
  

  //here we set up the LED

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
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
  

  if (request.indexOf("/RED") != -1){
    setColour(255, 0, 0);
    Serial.println("I am red!");
    }
  else if (request.indexOf("/GREEN") != -1){
    setColour(0, 255, 0);
    Serial.println("I am green!");
    }
  else if (request.indexOf("/BLUE") != -1){
    setColour(0, 0, 255);
    Serial.println("I am blue!");
    }


  // Prepare the HTML document to respond and add buttons:

  String s = "HTTP/1.1 200 OK\r\n";
  s += "Content-Type: text/html\r\n\r\n";
  s += "<!DOCTYPE HTML>\r\n<html>\r\n";
  s += "<br><input type=\"button\" name=\"b1\" value=\"Turn LED GREEN\" onclick=\"location.href='/GREEN'\">";  
  s += "<br><br><br>";
  s += "<br><input type=\"button\" name=\"b1\" value=\"Turn LED BLUE\" onclick=\"location.href='/BLUE'\">";
  s += "<br><br><br>";  
  s += "<br><input type=\"button\" name=\"b1\" value=\"Turn LED RED\" onclick=\"location.href='/RED'\">";
  s += "</html>\n";
  
  //Serve the HTML document to the browser.
  
  client.flush(); //clear previous info in the stream 
  client.print(s); // Send the response to the client 
  delay(1); 
  Serial.println("Client disonnected"); //Looking under the hood
}

  void setColour(int red, int green, int blue)
  {

  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;

  analogWrite(redPin, red);
  analogWrite(bluePin, blue);
  analogWrite(greenPin, green);
  }



