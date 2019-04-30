#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

const int RXPin = D3;
const int TXPin = D4;

const int RX = D1;
const int TX = D2;

TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);
SoftwareSerial node(RX, TX);

#define AIO_KEY "aa0accf184b344e3b07befd2da1e48a8"

const char* ssid = "joshua"; // your wireless network name (SSID) D (12345678)
const char* password = "josh1234"; // your Wi-Fi network password

WiFiClient client;
HTTPClient http;
int httpCode;

String getURL = "http://io.adafruit.com/api/v2/JoshDcu/feeds/dest/data/retain";
String postURL = "http://io.adafruit.com/api/v2/JoshDcu/feeds/pres/data";
String payloadG, payloadP, coordStrNew;
String coordStr = " ";

//float presLat, presLong;
float presLat = 13.010674, presLong = 74.794154;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  ss.begin(9600);
  node.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.print("IP address: "); Serial.println(WiFi.localIP());  

  Serial.print(F("Obtaining GPS location data"));
  while (!gps.location.isValid()){
    Serial.print(".");
    while (ss.available() > 0){
      gps.encode(ss.read()); 
    }
  
    if (gps.location.isValid()){
      presLat = gps.location.lat();
      presLong = gps.location.lng();
    }  
    delay(200);   
  }
  Serial.print(F("\nObtained GPS location data: "));
  Serial.print(presLat, 6);
  Serial.println(presLong, 6);
  
}

void loop() {
  // put your main code here, to run repeatedly:
//-----------------------POST COORDINATES-------------------------------
  http.begin(postURL);
  http.addHeader("X-AIO-Key", AIO_KEY);
  http.addHeader("Content-Type", "application/json");
  String post = "{\"value\":\"45\"}";
  httpCode=http.POST(post); 
  if (httpCode > 0)
  {
    if (httpCode == HTTP_CODE_OK)
    {
      Serial.println("OK!");
      payloadP = http.getString();
      Serial.println(payloadP);
    }
    else
    {
      Serial.println("Failed!");
    }
  }
  http.POST(post);
  http.end();
  delay(500);  
//-----------------------GET COORDINATES-------------------------------  
  http.begin(getURL);
  http.addHeader("X-AIO-Key", AIO_KEY);
  httpCode = http.GET();
  if (httpCode > 0)
  {
    if (httpCode == HTTP_CODE_OK)
    {
      Serial.println("OK!");
      payloadG = http.getString();
      Serial.println(payloadG);
      coordStrNew = String(String(presLong,6) + "," + String(presLat,6) + "%7C" + payloadG.substring(payloadG.indexOf(' ')+1, payloadG.length()-4) + payloadG.substring(1 , payloadG.indexOf(',')));
    }
    else
    {
      Serial.println("Failed!");
    }
  }
  http.end();
  delay(500);
//-----------------------FIND WAYPOINTS-------------------------------  
  if (!coordStrNew.equals(coordStr)){
    String payloadW;
    String wayURL = String("http://api.openrouteservice.org/directions?api_key=5b3ce3597851110001cf62485383b4ee48b94a959e10b53d60a66c74&coordinates=" + coordStr + "&profile=driving-car&format=geojson");
    http.begin(wayURL);
    httpCode = http.GET();
    if (httpCode > 0)
    {
      if (httpCode == HTTP_CODE_OK)
      {
        Serial.println("OK!");
        payloadW = http.getString();
        payloadW = payloadW.substring(41, payloadW.indexOf("]]")+1);
        Serial.println(payloadW);
        //node.println(payloadW);
      }
      else
      {
        Serial.println("Failed!");
      }
    }
    http.end();
    delay(500);
    coordStr = coordStrNew;
  }
}
