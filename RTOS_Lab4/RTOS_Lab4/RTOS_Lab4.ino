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

//Configure to use 1 CPU Core
#if CONFIG_FREETOS_UNICORE
static const BaseType_t cpu = 0;
#else
static const BaseType_t cpu = 1;
#endif

void t1_current(void *param);
void t2_ultrasonic(void *param);
void t3_transmit(void *param);

int sensor = 4;
int trigPin = 5;
int echoPin = 18;
int duration = 0;
int distance = 0;
int adc = 0;
int current = 0;

void setup() {
  pinMode(2, OUTPUT); // Set LEDs as output
  pinMode(sensor, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(115200); // Serial monitor setup
  Serial.begin(115200);
  delay(1000);
  Blynk.begin(auth, ssid, pass);
 
}

void loop() {

  Blynk.run();
  timer.run();

  xTaskCreatePinnedToCore(
    t1_current, //Calling task1 Function
    "Task1 - Cuurent", //Name of Task
    1024, //Stack Size
    NULL, //Function Parameters
    1, //Task Priority
    NULL, //Task Handle
    cpu); //Runs on 1 CPU Core


  xTaskCreatePinnedToCore(
    t2_ultrasonic, //Calling task1 Function
    "Task3_Transmit", //Name of Task
    1024, //Stack Size
    NULL, //Function Parameters
    1, //Task Priority
    NULL, //Task Handle
    cpu); //Runs on 1 CPU Core


  xTaskCreatePinnedToCore(
    t3_transmit, //Calling task1 Function
    "Task1 - Input", //Name of Task
    1024, //Stack Size
    NULL, //Function Parameters
    1, //Task Priority
    NULL, //Task Handle
    cpu); //Runs on 1 CPU Core

}


void t1_current(void *param) {
  adc = analogRead(4);
  current = adc;

  Serial.print("Current -> ");
  Serial.print(current);
  Serial.print(" mA\n");
  delay(1000);

}

void t2_ultrasonic(void *param) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.println("Distance: ");
  Serial.println(distance);
  delay(100);
}

void t1_transmit(void *param) {
  int h = distance;
  int t = current; 

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V5, h); 
  Blynk.virtualWrite(V6, t);
}
