#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266HTTPClient.h>
#include <SimpleTimer.h>
#include <Phant.h>
#include <DHT.h>
#define DHTTYPE DHT22
#define DHTPIN  D4
DHT dht(DHTPIN, DHTTYPE, D4);
float humidity, temp;  // Values read from sensor
unsigned long previousMillis = 0;
const long interval = 15000;          // interval at which to read sensor / Update values

// Auth Token App via Mail of printscreen
char auth[] = "1847ec45d79f4d4495d67d59101d3f77";

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, "G.E.C.K", "ewRiOrgRSqCE");
  dht.begin();}

void gettemperature() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you read the sensor
    previousMillis = currentMillis;

    // Reading temperature for humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (it's a very slow sensor)
    humidity = dht.readHumidity();          // Read humidity (percent)
    temp = dht.readTemperature(false);     // Read temperature as Fahrenheit


    // Serial Monitor
    Serial.print("Humidity ");
    Serial.print(humidity);
    Serial.println(" %\t");
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println(" *C ");

    Blynk.virtualWrite(V0, temp);
    Blynk.virtualWrite(V1, humidity);

    // Check if any reads failed and exit early (to try again).
    if (isnan(humidity) || isnan(temp)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
  }
}

bool isFirstConnect = true;
BLYNK_CONNECTED() {
  if (isFirstConnect)
  {
    Blynk.syncAll();
    isFirstConnect = false;
  }
}

void loop()
{
  Blynk.run();
  gettemperature();
}
