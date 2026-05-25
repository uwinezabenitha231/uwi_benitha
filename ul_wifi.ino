#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "muhura121";
const char* pass = "134567890";

const char* servername = "http://192.168.0.144/makaka/ignace.php";

#define trigpin 5
#define echopin 18
#define greenpin 21
#define bluepin 22
#define redpin 23

void setup() {

  Serial.begin(115200);

  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);

  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
  pinMode(redpin, OUTPUT);

  WiFi.begin(ssid, pass);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n=================");
  Serial.println("WiFi Connected");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("=================");
}

void loop() {

  digitalWrite(greenpin, LOW);
  digitalWrite(bluepin, LOW);
  digitalWrite(redpin, LOW);

  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigpin, LOW);

  long duration = pulseIn(echopin, HIGH);

  float distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    http.begin(servername);

    http.addHeader("Content-Type", "application/json");

    StaticJsonDocument<200> Makaka;

    Makaka["device_name"] = "esp32_01";
    Makaka["INTERA"] = distance;

    String Jsondoc;

    serializeJson(Makaka, Jsondoc);

    int responsecode = http.POST(Jsondoc);

    Serial.print("Sent JSON: ");
    Serial.println(Jsondoc);

    if (responsecode > 0) {

      String response = http.getString();

      Serial.print("Data inserted successfully. Response: ");
      Serial.println(response);

    }
    else {

      Serial.print("Server failed. Error: ");
      Serial.println(responsecode);
    }

    http.end();

  } 
  else {

    Serial.println("Failed to connect to WiFi.");
  }

  if (distance > 0 && distance <= 20) {

    digitalWrite(greenpin, HIGH);
  }
  else if (distance > 20 && distance <= 40) {

    digitalWrite(bluepin, HIGH);
  }
  else if (distance > 40 && distance <= 60) {

    digitalWrite(redpin, HIGH);
  }
  else {

    Serial.println("Safe on the gate");
  }

  delay(2000);
}
      


    
    
  
  


