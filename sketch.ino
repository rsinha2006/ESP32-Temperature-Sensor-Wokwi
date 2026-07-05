#include <DHT.h>
#include<Adafruit_Sensor.h>

#define DHTPIN 25
//digital pin connected to the DHT sensor

#define DHTTYPE DHT22

//connect pin 1 of the sensor to the +5v
//connect pin 2 of the sensor to the DHT pin 25
//connect pin 4 of the sensor to GROUND

DHT dht(DHTPIN, DHTTYPE);

void setup(){
  Serial.begin(115200);
  Serial.println(F("DHTxx test!"));

  dht.begin();
}

void loop(){
  //wait a few seconds between measurements
  delay(2000);

  //reading temperature or humidity takes about 250 milliseconds
  //sensor readings may also take up to 2 seconds (it's a very slow sensor)

  float h = dht.readHumidity();
  //read temperature as Celsius (the default)

  float t = dht.readTemperature();
  //read temperature as Fahrenheit (isFahrenheit = True)

  float f = dht.readTemperature(true);

  //check if any read failed and exist early (to try again)
  if(isnan(h) || isnan(t) || isnan(f)){
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  //compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);

  //compute heat index in Celsius(isFahrenheit = False)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F Heat Index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F "));
}
