// please check the video
// https://www.youtube.com/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "ESP";
const char* password = "123456789";

MDNSResponder mdns;

String Domain = "home";
String switch1name = "Light";
String switch1 = "OFF";

ESP8266WebServer server(80);

void handleRoot() {
 server.send(200, "text/html", 
"<!DOCTYPE html>" \
"<html>" \
"<head>" \
"<title>home</title>" \
"</head>" \
"<body>" \
"<h1>Home Automation</h1>" \
"<h2>"+ switch1name +": "+ switch1 +"</h2>" \
"<p><a href=\"/Switch1ON\"><button class=\"button\">ON</button></a><a href=\"/Switch1OFF\"><button class=\"button\">OFF</button></a></p>" \
"</body>" \
"</html>" \
);
}

void switch1ON(){
  switch1 = "ON";
  digitalWrite(D1, LOW);
  handleRoot();
}

void switch1OFF(){
  switch1 = "OFF";
  digitalWrite(D1, HIGH);
  handleRoot();
}

void setup(void){
  pinMode(D1, OUTPUT);
  pinMode(D4, OUTPUT);
  digitalWrite(D4, HIGH);
  digitalWrite(D1, HIGH);
  
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); 

  if(mdns.begin(Domain)){
    Serial.println("MDNS Started: " + Domain + ".local/");
  }
 
  server.on("/", handleRoot);   
  server.on("/Switch1ON", switch1ON);  
  server.on("/Switch1OFF", switch1OFF);      

  server.begin();                 
  Serial.println("HTTP server started");
  digitalWrite(D4, LOW);
}

void loop(void){
  mdns.update();
  server.handleClient();  
}