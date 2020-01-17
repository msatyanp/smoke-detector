/* ESP & Blynk */
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Blynk.h>
#include <DHT.h>
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
char auth[] = "<bylnk auth key>";
 
/* WiFi credentials */
char ssid[] = "<Your WIFI>";
char pass[] = "<password>";

#define DHTPIN 0          // D3
 
// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11

 
 
 
int mq135 = A0; // smoke sensor is connected with the analog pin A0 
int data = 0; 
void setup() 
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, getSendData);
}
 
void loop() 
{
  timer.run(); // Initiates SimpleTimer
  Blynk.run();
}
 
/***************************************************
 * Send Sensor data to Blynk
 **************************************************/
void getSendData()
{
data = analogRead(mq135); 
  Blynk.virtualWrite(V2, data); //virtual pin V3
 
  if (data > 600 )
  {
    Blynk.notify("Smoke Detected!!!"); 
  }
 
}

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
 
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, t);
  Blynk.virtualWrite(V6, h);
}
