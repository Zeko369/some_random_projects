#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include "DHT.h"

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
#define DHTPIN 8
DHT dht(DHTPIN, DHTTYPE);

void setup()   
{                
	Serial.begin(9600);

	dht.begin();
	bmp.begin();

	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

	display.display();
	delay(2000);

	display.clearDisplay();

	// text display tests
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(0,0);
	display.println("Hello, world!");
	display.setTextColor(BLACK, WHITE); // 'inverted' text
	display.println(3.141592);
	display.setTextSize(2);
	display.setTextColor(WHITE);
	display.print("0x"); display.println(0xDEADBEEF, HEX);
	display.display();
	delay(2000);
	display.clearDisplay();
}


void loop() 
{
	float temperature, a;
	float seaLevelPressure = 1013.25;

	sensors_event_t event;
	bmp.getEvent(&event);
	bmp.getTemperature(&temperature);
	a = bmp.pressureToAltitude(seaLevelPressure, event.pressure); 
	
	float h = dht.readHumidity();
	float t = dht.readTemperature();

	display.clearDisplay();
	display.setCursor(0, 0);
	display.setTextSize(1);
	display.setTextColor(WHITE);

	display.print("Pressure: ");
	display.print(event.pressure);
	display.println("hPa");
	display.println("");

	display.print("Temp: ");
	display.print(temperature);
	display.println(" C");
	display.println("");

	display.println("DHT22: ");
	display.print("Temp: ");
	display.print(t);
	display.print(" C");
	display.println("");
	display.print("Hum: ");
	display.print(h);
	display.println("%");

	display.display();
	delay(2000);	
}
