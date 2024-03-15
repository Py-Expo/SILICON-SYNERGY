// you can reference the video https://youtu.be/MXFFoh1oZhE from makers group YouTube channel
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#define soil_moisture_pin D0
#define HOST "localhost:3307"
#define WIFI_SSID "PYEXPO24"
#define WIFI_PASSWORD "PYexp0#24$"

String sendval,  postData;

void checkWiFiConnection() 
{

  while (WiFi.status() != WL_CONNECTED)
   {
    Serial.println("Connecting to Wi-Fi...");
    delay(1000);
  }

  Serial.println("Connected to Wi-Fi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

}

void setup() 
{
  Serial.begin(115200);
  Serial.println("Communication Started\n");

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  checkWiFiConnection();
}

void loop()
 {
  checkWiFiConnection();
  WiFiClient client;
  HTTPClient http;

  int Moisturelevel = (analogRead(soil_moisture_pin));// you can get the actual value from attached sensor
  //int humidity = random(60,90);// you can get the actual value from attached sensor
  Serial.println(analogRead(soil_moisture_pin));
  delay(500);
  sendval = String(Moisturelevel);
  //sendval2 = String(humidity);

  postData = "sendval=" + sendval;
  Serial.print("Sending data: ");
  Serial.println(postData);

  http.begin(client, "http://172.16.89.50/dht11_project/moisture.php");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int httpCode = http.POST(postData);

  if (httpCode == HTTP_CODE_OK) 
  {
    String response = http.getString();
    Serial.println("Server response: " + response);
  } 
  
  else
  {
    Serial.print("HTTP POST request failed with error code: ");
    Serial.println(httpCode);
    if (httpCode == HTTPC_ERROR_CONNECTION_REFUSED)
    {
      Serial.println("Connection refused by the server.");
    }
    else if (httpCode == HTTP_CODE_NOT_FOUND) 
    {
      Serial.println("Server resource not found.");
    }
    else {
      Serial.println("Unknown error occurred.");
    }
  }

  http.end();
  delay(5000);
}