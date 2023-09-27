//*******************************includes********************************
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <SoftwareSerial.h>
//***********************************************************************
const int rst = 2, enr = 3;
SoftwareSerial sensor(7, 8); // rx , tx 

const char* ssid = "yourSSID";
const char* password = "yourPASSWD";

//Your Domain name with URL path or IP address with path
String serverName = "http://192.168.253.128:80/";

uint8_t id; // for incoming serial data

void setup() {
  pinMode(enr, INPUT_PULLUP);
  pinMode(rst, INPUT_PULLUP);

  sensor.begin(115200); // opens serial port, sets data rate to 9600 bps
  Serial.begin(115200); 

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  //Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED){
    if ( (digitalRead(rst) == LOW) && !(digitalRead(enr) == LOW) ) {
      WiFiClient client;
      HTTPClient http;
      if (sensor.available() > 0) {
        String serverPath = serverName + "resetter.php/";

        // Your Domain name with URL path or IP address with path
        http.begin(client, serverPath.c_str());
          
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
    } else if ( (digitalRead(enr) == LOW) && !(digitalRead(rst)  == LOW) ) {
      if (Serial.available() > 0) {
        WiFiClient client;
        HTTPClient http;
        // read the incoming byte:
        id = sensor.read();
        String serverPath = serverName + "enroller.php/";
        serverPath = serverPath + "?id=";
        serverPath = serverPath + id;

        // Your Domain name with URL path or IP address with path
        http.begin(client, serverPath.c_str());
          
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
    } else if ( (digitalRead(enr) == LOW) && (digitalRead(rst) == LOW) ) {
      if (Serial.available() > 0) {
        WiFiClient client;
        HTTPClient http;
        // read the incoming byte:
        id = sensor.read();
        String serverPath = serverName + "deleter.php/";
        serverPath = serverPath + "?id=";
        serverPath = serverPath + id;

        // Your Domain name with URL path or IP address with path
        http.begin(client, serverPath.c_str());
          
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
    } else {
      if (Serial.available() > 0) {
        WiFiClient client;
        HTTPClient http;
        // read the incoming byte:
        id = sensor.read();
        String serverPath = serverName + "listener.php/";
        serverPath = serverPath + "?id=";
        serverPath = serverPath + id;

        // Your Domain name with URL path or IP address with path
        http.begin(client, serverPath.c_str());
          
        // Send HTTP GET request
        int httpResponseCode = http.GET();
        
        if (httpResponseCode>0) {
          Serial.print("HTTP Response code: ");
          Serial.println(httpResponseCode);
          String payload = http.getString();
          Serial.println(payload);
          sensor.print(payload);
        }
        else {
          Serial.print("Error code: ");
          Serial.println(httpResponseCode);
        }
        // Free resources
        http.end();
      }
    }
  } else {
    Serial.println("WiFi Disconnected");
  }
}
