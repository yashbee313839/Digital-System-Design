#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <SPI.h>
#include <Wire.h>
#include <QMC5883L.h>

const int enAL = 6;
const int enBR = 9;
const int in2 = 5;
const int in3 = 7;

/*13.011478,74.791992
13.011333,74.792076
13.011410,74.792549
13.011243,74.792564*/
static const int RXPin = 4, TXPin = 8;
//static const int RX = A1, TX = A2;

float presLat = 0.0;
float presLong = 0.0;
float destLat = 0.0;
float destLong = 0.0;

float error = 0.0;
float pastError = 0.0;
float pastErrors = 0.0;
float range = 0.0;
float bearing = 0.0;
const float KP = 5.0;
const float KI = 0.0;
const float KD = 10.0;

int x, y, z;
const float declinationAngle = -0.018617;//0.0404;

boolean done = false;
//13.010902,74.794479
//13.010923,74.794616

//13.011190,74.794517

//13.010654,74.793960
//13.010670,74.794166
//13.010964,74.794166
float latArr[] = {13.011478, 13.011333, 13.011410, 13.011243};//{13.010654, 13.010670, 13.010964};//{13.011190};//{13.010673, 13.010706, 13.010772, 13.010908, 13.010953, 13.010978, 13.010986, 13.010981, 13.010979, 13.010977};
float longArr[] = {74.791992, 74.792076, 74.792549, 74.792564};//{74.793960, 74.794166, 74.794166};//{74.794517};//{74.794176, 74.794176, 74.794176, 74.794176, 74.794096, 74.793886, 74.793822, 74.793486, 74.793203, 74.793083};
int count = 0;
int lenArr = 3;

TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);
QMC5883L compass;

void setup(){
  pinMode(enAL, OUTPUT);
  pinMode(enBR, OUTPUT);  
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  SPI.begin();
  Serial.begin(9600);
  Wire.begin();
  compass.init();
  ss.begin(9600);

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
    delay(500);   
  }
  Serial.print(F("\nObtained GPS location data: "));
  Serial.print(presLat, 6);
  Serial.println(presLong, 6);
 // moveBot(200, 200, 0);
  destLat = latArr[count];
  destLong = longArr[count];
}

void loop(){
  range = TinyGPSPlus::distanceBetween(presLat, presLong, destLat, destLong);
  bearing = TinyGPSPlus::courseTo(presLat, presLong, destLat, destLong);
  while (range > 3.5)
  {
    while (ss.available() > 0){
      gps.encode(ss.read());
    }
  
    if (gps.location.isValid()){
      presLat = gps.location.lat();
      presLong = gps.location.lng();
      Serial.print(F("presLat: ")); Serial.print(presLat,6); Serial.print(F(" presLong: ")); Serial.println(presLong,6);
    }
    
    compass.read(&x,&y,&z);
    float heading = atan2(y, x);
    heading += declinationAngle;
    if(heading < 0)
      heading += 2*PI;
    if(heading > 2*PI)
      heading -= 2*PI;
    heading = heading * 180/M_PI; 
    Serial.print(F("heading: ")); Serial.print(heading); Serial.print(F(" bearing: ")); Serial.println(bearing);
    
    error = bearing - heading;
    if (bearing > heading){
      if ((abs(bearing - heading)) < abs(-360+bearing-heading)){
        error = bearing - heading;
      }
      else{
        error = -360+bearing-heading; 
      }
    }
    else{
      if ((abs(bearing - heading)) < abs(360+bearing-heading)){
        error = bearing - heading;
      }
      else{
        error = 360+bearing-heading;
      }
    }
    /*if (error < -180)
      error += 360;
    else if (error > 180) //this will make the robot move only towards the left. It's buggy that's why
      error -=360;*/
      
    if (abs(error) >= 5.0){
      int pwm = (int)((KP*error) + (KI*(error+pastErrors)) + (KD*(error-pastError)));
      if (abs(pwm) < 70){
        if (pwm > 0) pwm = 70;
        else pwm = -70;
      }
      if (abs(pwm) > 255){
        if (pwm > 0) pwm = 255;
        else pwm = -255;
      }
      Serial.print(F("error: ")); Serial.print(error); Serial.print(F(" pwm: ")); Serial.println(pwm);
      moveBot(pwm, -pwm, 0);
      pastErrors += error;   
      pastError = error;      
    }
    else{
      pastErrors = 0;
      pastError = 0;
      moveBot(200, 200, 0);
    }
//    bearing = TinyGPSPlus::courseTo(presLat, presLong, destLat, destLong);
    range = TinyGPSPlus::distanceBetween(presLat, presLong, destLat, destLong); 
    Serial.print(F("pastError: ")); Serial.print(pastError); Serial.print(F(" range: ")); Serial.println(range);
    Serial.print(F("count: ")); Serial.println(count);
  }
  if (range <= 3.5){
    count = count + 1;
    if (count == lenArr){
      Serial.println("All done!");
      moveBot(0, 0, 0);
      while(true);
    }
    else{
      destLat = latArr[count];
      destLong = longArr[count];           
    }
  }
}

void moveBot(int left, int right, int del){
  if (left < 0){
    digitalWrite(in2, HIGH);
  }
  else{
    digitalWrite(in2, LOW);
  }
  if (right < 0){
    digitalWrite(in3, LOW);
  }
  else{
    digitalWrite(in3, HIGH);
  }
  int sL = abs(left);
  int sR = abs(right);
  analogWrite(enAL, sL);
  analogWrite(enBR, sR);    
  if (del) delay(del);
}


