/* https://circuits4you.com
 *  ESP32 Internal Temperature Sensor Example */
 
#ifdef __cplusplus
extern "C" 
{
  #endif
  uint8_t temprature_sens_read();
  #ifdef __cplusplus
}
#endif
 
uint8_t temprature_sens_read();
#include<WiFi.h>
WiFiClient client;
String thingSpeakAddress = "api.thingspeak.com";
String writeAPIKey;
String tsfield1Name;
String request_string;
const char *ssid =  "";                        // replace with your wifi ssid and wpa2 key
const char *pass =  ""; 
float temp;
void setup() 
{
  Serial.begin(115200);
  WiFi.disconnect();
  WiFi.begin(ssid, pass);
  while ((!(WiFi.status() == WL_CONNECTED))) 
  {
    delay(300);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
 
void loop() 
{
  temp = (temprature_sens_read() - 32) / 1.8;
  Serial.print("Temperature: ");
  Serial.print(temp);  // Konversi F ke C
  Serial.println(" C");
  kirim_thingspeak(temp);
}

void kirim_thingspeak(float suhu) 
{
  if (client.connect("api.thingspeak.com", 80)) 
  {
    request_string = "/update?";
    request_string += "key=";
    request_string += "L24WLXK7I9AGVJ9V"; // diubah sesuai dengan KEY pada channel
    request_string += "&";
    request_string += "field1";
    request_string += "=";
    request_string += suhu;
 
    Serial.println(String("GET ") + request_string + " HTTP/1.1\r\n" +
                 "Host: " + thingSpeakAddress + "\r\n" +
                 "Connection: close\r\n\r\n");
                 
    client.print(String("GET ") + request_string + " HTTP/1.1\r\n" +
                 "Host: " + thingSpeakAddress + "\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) 
    {
      if (millis() - timeout > 5000) 
      {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
      }
    }
 
    while (client.available()) 
    {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
    Serial.println();
    Serial.println("closing connection");
  }
}
