//will work on Attiny85/45//RF433=D0 pin 5
//DHT=D4 pin 3

// libraries
#include "DHT.h"
#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 11

#include <Manchester.h>
DHT dht(DHTPIN, DHTTYPE);

#define TX_PIN 8  //pin where your transmitter is connected
//variables
float h=0;
float t=0;
int transmit_t = 0;
int transmit_h = 0;
int transmit_data = 0;
int ctr = 0;
void setup() {
  pinMode(2, INPUT);
  man.setupTransmit(TX_PIN, MAN_300);
  
  Serial.begin(9600);
  Serial.println("DHT transmitter v 1.0");
}

void loop() {
 //int chk = dht.readHumidity();
// h=dht.humidity;
// t=dht.temperature;

delay(2000);

 
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
 // Check if any reads failed and exit early (to try again).

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

 
// I know, I am using 3 integer variables here
// where I could be using 1
// but that is just so it is easier to follow

 transmit_h=100* (int) h;
 transmit_t=(int) f;
 transmit_data=transmit_h+transmit_t;
  man.transmit(transmit_data);
  Serial.print("Counter= ");
  Serial.print(ctr);
  Serial.print("  temp= ");
  Serial.println(transmit_t);
  delay(500);
  ctr = ctr + 1;
}

