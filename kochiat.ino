#include <ESP8266WiFi.h>

#define TRIGGER 5
#define ECHO    4

// data Accesspoint
const char* ssid = "zx";
const char* password = "poiuytrewq";
const char* host = "zxdot.tk";
const int port = 80;
String value;

void setup()
{ 
  Serial.begin(9600);
  Serial.println();
  Serial.print("Starting WiFi...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }
    if(WiFi.status()) Serial.println(" wifi !");
   WiFiClient client;
   
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUILTIN_LED, OUTPUT);
  
  long duration, distance;
  digitalWrite(TRIGGER, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(TRIGGER, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = (duration/2) / 29.1;
  
  Serial.print(distance);
  Serial.println("Centimeter:");
  delay(1000);
  
  if(distance<=10) value="100";
  else if(distance<=25) value="50";
  else value="10";
  
  Serial.println(value);
  

  if(client.connect(host, port)) 
  {

    Serial.println("connecton");
    String data="?sender=akhbfa&value=";
    data+=value;
    
    client.print(String("GET ") + data + " HTTP/1.1\r\n" +
                   "Host: " + host + "\r\n" + 
                   "Connection: close\r\n\r\n");
    Serial.println("sent");
  }
    if (!client.connect(host, port))
  {
    Serial.print(" fail");
  }
  
}
void loop()
{ 
}
