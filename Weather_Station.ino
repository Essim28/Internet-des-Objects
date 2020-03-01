
// Import required libraries
#ifdef ESP32
  #include <WiFi.h>
  #include <ESPAsyncWebServer.h>
  #include <SPIFFS.h>
#else
  #include <Arduino.h>
  #include <ESP8266WiFi.h>
  #include <Hash.h>
  #include <ESPAsyncTCP.h>
  #include <ESPAsyncWebServer.h>
  #include <FS.h>
#endif
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


// current temperature & humidity, updated in loop()
float t = 0.0;
float h = 0.0;
float A = 1.11492089e-3;
float B = 2.372075385e-4;
float C = 6.954079529e-8;
float celsius;
const long interval = 10000;  
const int Rc = 10000;
const int Vcc = 3;
const int SensorPIN = A0;
float K=2.5;
unsigned long previousMillis = 0;    // will store last time DHT was updated

// To configure our Wifi network

const char* ssid = "TP-LINK_55B2";
const char* password = "36899029";

//const char* ssid = "TP-LINK_28F0";
//const char* password = "72271636";

// Create our server on port 80
AsyncWebServer server(80);

String readSensorTemperature() {
  // Read temperature as Celsius with our thermistor
  
 float raw = analogRead(SensorPIN);
 float V =  raw / 1024 * Vcc;

 float R = (Rc * V ) / (Vcc - V);


 float logR  = log(R);
 float R_th = 1.0 / (A + B * logR + C * logR * logR * logR );

  float kelvin = R_th - V * V / (K * R) * 1000;
  celsius = kelvin - 273.15;
    float t=celsius;  
    
  if (isnan(t)) {    
    Serial.println("Failed!");
    return "";
  }
  else {
    Serial.println(t);
    return String(t);
  }
}
 


String readSensorHumidity() {
  dht.begin();

  
  float h = dht.readHumidity();
  if (isnan(h)) {
    Serial.println("Failed!");
    return "";
  }
  else {
    Serial.println(h);
    return String(h);
  }
}




// Replaces placeholder (web server) with DHT values
String processor(const String& var){
  //Serial.println(var);
  if(var == "TEMPERATURE"){
    return String(t);
  }
  else if(var == "HUMIDITY"){
    return String(h);
  }
  return String();
}


void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  
  dht.begin();


  // Initialize SPIFFS
  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html");
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readSensorTemperature().c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(h).c_str());
  });
 

  // Start server
  server.begin();
}
 
void loop(){
  unsigned long currentMillis = millis();


  if (currentMillis - previousMillis >= interval) {
    // save the last time you updated the DHT values
    previousMillis = currentMillis;
    // Read temperature as Celsius (the default)



  float raw = analogRead(SensorPIN);
  float V =  raw / 1024 * Vcc;

  float R = (Rc * V ) / (Vcc - V);


  float logR  = log(R);
  float R_th = 1.0 / (A + B * logR + C * logR * logR * logR );

  float kelvin = R_th - V * V / (K * R) * 1000;
  celsius = kelvin - 273.15;
  float newT=celsius;




    
    // if temperature read failed, don't change t value
    if (isnan(newT)) {
      Serial.println("Failed to read from DHT sensor!");
    }
    else {
      t = newT;
      Serial.println(t);
    }
    // Read Humidity
    float newH = dht.readHumidity();
    // if humidity read failed, don't change h value 
    if (isnan(newH)) {
      Serial.println("Failed!");
    }
    else {
      h = newH;
      Serial.println(h);
    }
  }
}
