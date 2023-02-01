/*************************************************************
  WARNING!
    It's very tricky to get it working. Please read this article:
    http://help.blynk.cc/hardware-and-libraries/arduino/esp8266-with-at-firmware
  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPLT0OeMyff"
#define BLYNK_DEVICE_NAME "stutemiot"
#define BLYNK_AUTH_TOKEN "Qdi1gIfqaya79pDG9-sSsErXBbgwPduT"


// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial


#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <DHT.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "GxA50";
char pass[] = "iemx6540";

// Hardware Serial on Mega, Leonardo, Micro...
//#define EspSerial Serial1

// or Software Serial on Uno, Nano...
#include <SoftwareSerial.h>
SoftwareSerial EspSerial(4, 5); // RX, TX

// Your ESP8266 baud rate:
#define ESP8266_BAUD 9600

ESP8266 wifi(&EspSerial);

const int ldrPin = A0;
const int moistPin = A2;
const int rainPin = A1;

#define DHTPIN D6
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  //*****LDR Sensor Routine*****//
  Serial.println("Reading LDR...");
  int ldrStatus = analogRead(ldrPin);
  Blynk.virtualWrite(V5, ldrStatus);
  delay(5);

  // Read temperature as Celsius (the default)
  Serial.println("Reading DHT...");
  int h = dht.readHumidity();
  int t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V6, t);
  delay(5);

  //*****Soil Moisture Sensor Routine*****//
  Serial.println("Reading moisture...");
  int moistStatus = analogRead(moistPin);
  Blynk.virtualWrite(V7, moistStatus);
  delay(5);

    //*****Soil Moisture Sensor Routine*****//
  Serial.println("Reading rain...");
  int rainStatus = analogRead(rainPin);
  Blynk.virtualWrite(V8, rainStatus);
  delay(5);

  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V2, millis() / 1000);
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  
  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  //Blynk.begin(auth, wifi, ssid, pass);
  // You can also specify server:
  Blynk.begin(auth, wifi, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, wifi, ssid, pass, IPAddress(192,168,1,100), 8080);

  dht.begin();
  
  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}
