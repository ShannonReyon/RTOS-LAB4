#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLljL2llOr"
#define BLYNK_DEVICE_NAME "RTOSLAB4"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "U8-3YP5wGFdQ5gdw79QALC5M0oc9wdpw";
char ssid[] = "EN20401726";
char pass[] = "12345678";

BlynkTimer timer;

int current = 0;
int distance = 0;

void sendSensor()
{
for(int i=0;i<200;i++){
  current = current + 1;
  Blynk.virtualWrite(V5, current);
  distance = distance + 1;
  Blynk.virtualWrite(V6, distance);
}
for(int i=0;i<200;i++){
  current = current - 1;
  Blynk.virtualWrite(V5, current);
  distance = distance - 1;
  Blynk.virtualWrite(V6, distance);
}

}

void setup()
{
  Serial.begin(115200);
  delay(1000);
  Blynk.begin(auth, ssid, pass);
 
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
