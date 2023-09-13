// #include <BearSSLHelpers.h>
// #include <CertStoreBearSSL.h>
// #include <ESP8266WiFi.h>
// #include <ESP8266WiFiAP.h>
// #include <ESP8266WiFiGeneric.h>
// #include <ESP8266WiFiGratuitous.h>
// #include <ESP8266WiFiMulti.h>
// #include <ESP8266WiFiSTA.h>
// #include <ESP8266WiFiScan.h>
// #include <ESP8266WiFiType.h>
// #include <WiFiClient.h>
// #include <WiFiClientSecure.h>
// #include <WiFiClientSecureBearSSL.h>
// #include <WiFiServer.h>
// #include <WiFiServerSecure.h>
// #include <WiFiServerSecureBearSSL.h>
// #include <WiFiUdp.h>
// #include <ThingSpeak.h>
// #include "MQ135.h"
// #include <Adafruit_SSD1306.h>
// #include<ESP8266WiFi.h>
// #include<ThingSpeak.h>
// #include "MQ135.h"
// #include <SoftwareSerial.h>
//#include "Wifi.h"
// #include <Adafruit_GFX.h>

#include <ESP8266HTTPClient.h>

#include <ArduinoWiFiServer.h>
#include<WiFiClient.h>
#include<WiFiClientSecure.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include "ThingSpeak.h"
#include "MQ135.h"

#define ANALOGPIN A0
#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701
const char* ssid="";//insert wifi name
const char* password="";//insert wifi password
const char* host="maker.ifttt.com";
const int httpsPort=443;

const char* fingerprint="616275faea5f64954af6090f59c90de71e6d66a3";//on the ifttt site go to the lock icon at the top search bar->click on connection is secure->
//click on certificate is valid->at the end in the fingerprint section copy the sha-1 fingerprint 





WiFiClient client;


long myChannelNumber = 1965781;
const char myWriteAPIKey[] = "FOOGGYV1DN33Z1RX";

const int trigPin = 12;
const int echoPin = 14;
long duration;
float distanceCm;
float distanceInch;
//int t = 1;
MQ135 gasSensor = MQ135(ANALOGPIN);

int sensor_pin = 13; //NodeMCU On Board LED D7



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(20000);
  Serial.print("connecting to ");
  Serial.println(ssid);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  pinMode(sensor_pin, INPUT); //Set pin D7 as an input
  pinMode(LED_BUILTIN, OUTPUT);

  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print("..");
  }
  Serial.println("");
  Serial.println("Wifi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  // Serial.println("NodeMCU is connected!");
  // Serial.println(WiFi.localIP());
  ThingSpeak.begin(client);
  //mySerial.begin(115200);
   // Print the IP address
  // Serial.print("Use this URL to connect: ");
  // Serial.print("http://");
  // Serial.print(WiFi.localIP());
  // Serial.println("/");
  // digitalWrite(LED_BUILTIN, HIGH);



//https://maker.ifttt.com/trigger/esp_manhole/with/key/mhPbDCf_MW2cfCa9haSmWaKS690cK6Y8RGVqidGOOw6/?value1=9&value2=1&value3=90
}

void loop() {
  // if(Serial.available()>0)
  // {
  String text;
//while(t!=0) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  //display.setCursor(0, 25);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_VELOCITY/2;
  
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  if (distanceCm <= 20)
  { text="Water Level Reached";
    Serial.println("Water Level Reached");
    WiFiClientSecure client;
    Serial.print("connecting to");
    Serial.println(host);
    Serial.print("Using fingerprint: ");
    Serial.println(fingerprint);
    client.setFingerprint(fingerprint);
    if(!client.connect(host, httpsPort)){
      Serial.println("connection failed");
      return;
    }
    String url = "https://maker.ifttt.com/trigger/esp_manhole/with/key/mhPbDCf_MW2cfCa9haSmWaKS690cK6Y8RGVqidGOOw6?value1="+(String)text;//use the website link from the ifttt platform->in the github readme i have added the details
    Serial.print("requesting url: ");
    Serial.println(url);
    client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "User-Agent: BuildFailureDetectorESP8266\r\n" + "Connection: close\r\n\r\n");
    Serial.println("request sent");
  }
  float R0 = 15000;
  int sensorValue = analogRead(A0);
  float sensor_volt=(float)sensorValue/1024*5.0;
  float RS_gas = (5.0-sensor_volt)/sensor_volt;
  float ratio = RS_gas/R0;
  float x = 1000*ratio; 
  float LPG_PPM = pow(x,-1.431);//LPG PPM
  // Serial.print("LPG PPM = ");
  // Serial.println(LPG_PPM);

  //float ppm = gasSensor.getPPM();
  Serial.print("PPM Level: ");
  Serial.println(LPG_PPM);
  if (LPG_PPM > 80.00)
  { 
    text="Gas Detected";
    Serial.println("Gas Detected"); 
    WiFiClientSecure client;
    Serial.print("connecting to");
    Serial.println(host);
    Serial.print("Using fingerprint: ");
    Serial.println(fingerprint);
    client.setFingerprint(fingerprint);
    if(!client.connect(host, httpsPort)){
      Serial.println("connection failed");
      return;
    }
    String url = "https://maker.ifttt.com/trigger/esp_manhole/with/key/mhPbDCf_MW2cfCa9haSmWaKS690cK6Y8RGVqidGOOw6?value1="+(String)text;
    Serial.print("requesting url: ");
    Serial.println(url);
    client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "User-Agent: BuildFailureDetectorESP8266\r\n" + "Connection: close\r\n\r\n");
    Serial.println("request sent");
    // mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
    // updateSerial();
    // mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
    // updateSerial();
    // mySerial.println("AT+CMGS=\""+PHONE+"\"\r");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
    // updateSerial(); 
    // mySerial.println("Gas Detected"); //text content
    // updateSerial();
    // mySerial.write(0x1A);
    // delay(1000);
    // Serial.println("SMS Sent Successfully.");
  }
  int val_digital = digitalRead(sensor_pin);
  Serial.print("Tilt: ");
  Serial.println(val_digital);
  
  if(val_digital) {
    text="Tilt Detected";
    Serial.println("Tilt Detected");
    digitalWrite (LED_BUILTIN, HIGH);
    WiFiClientSecure client;
    Serial.print("connecting to");
    Serial.println(host);
    Serial.print("Using fingerprint: ");
    Serial.println(fingerprint);
    client.setFingerprint(fingerprint);
    if(!client.connect(host, httpsPort)){
      Serial.println("connection failed");
      return;
    }
    String url = "https://maker.ifttt.com/trigger/esp_manhole/with/key/mhPbDCf_MW2cfCa9haSmWaKS690cK6Y8RGVqidGOOw6?value1="+(String)text;
    Serial.print("requesting url: ");
    Serial.println(url);
    client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "User-Agent: BuildFailureDetectorESP8266\r\n" + "Connection: close\r\n\r\n");
    Serial.println("request sent");
        //Serial.print("Tilt Detected"); 
    // mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
    // updateSerial();
    // mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
    // updateSerial();
    // mySerial.println("AT+CMGS=\""+PHONE+"\"\r");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
    // updateSerial();
    // mySerial.println("Tilt Detected"); //text content
    // updateSerial();
    // mySerial.write(0x1A);
    // delay(1000);
    // Serial.println("SMS Sent Successfully.");
  }
  digitalWrite (LED_BUILTIN, LOW);

  ThingSpeak.writeField(myChannelNumber, 1, val_digital, myWriteAPIKey);
  
  ThingSpeak.writeField(myChannelNumber, 2, LPG_PPM, myWriteAPIKey);

  ThingSpeak.writeField(myChannelNumber, 7, distanceCm, myWriteAPIKey);

  delay(2000);
  // WiFiClient client;
  // Serial.print("connecting to");
  // Serial.println(host);
  // Serial.print("Using fingerprint: ");
  // Serial.println(fingerprint);
  // client.setFingerprint(fingerprint);
  // if(!=client.connect(host, httpsPort)){
  //   Serial.println("connection failed");
  // }
  // String url = "//https://maker.ifttt.com/trigger/esp_manhole/with/key/mhPbDCf_MW2cfCa9haSmWaKS690cK6Y8RGVqidGOOw6?value1="+(String)text;
  //t=0;
//}

 }
//}
