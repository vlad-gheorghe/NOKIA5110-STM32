/*********************************************************************
This is an example sketch for our Monochrome Nokia 5110 LCD Displays

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/338

These displays use SPI to communicate, 4 or 5 pins are required to
interface

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#define DHTPIN            PA0   
// Uncomment the type of sensor in use:
#define DHTTYPE           DHT11     // DHT 11 
//#define DHTTYPE           DHT22     // DHT 22 (AM2302)
//#define DHTTYPE           DHT21     // DHT 21 (AM2301)

// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

// pin PA5 - Serial clock out (SCLK)
// pin PA7 - Serial data out (DIN)
// pin PB7 - Data/Command select (D/C)
// pin PB8 - LCD chip select (CS)
// pin PB9 - LCD reset (RST)



Adafruit_PCD8544 display = Adafruit_PCD8544(PB7, PB8, PB9);


void setup()   {
  Serial.begin(9600);

  display.begin();
  // init done
 dht.begin();
  // you can change the contrast around to adapt the display
  // for the best viewing!
  display.setContrast(50);

  //display.display(); // show splashscreen
  //delay(2000);
  display.clearDisplay();   // clears the screen and buffer
 sensor_t sensor;
  dht.temperature().getSensor(&sensor);
   dht.humidity().getSensor(&sensor);
    delayMS = sensor.min_delay / 1000;
 
}


void loop() {
   delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;  
  dht.temperature().getEvent(&event);
 // dht.humidity().getEvent(&event);
  display.clearDisplay();

 
  display.setTextSize(1);
// display.setTextColor(BLACK);
 display.setCursor(10,0);
 //display.setTextColor(WHITE,BLACK);
 
  display.println("Temperatura");
 display.setCursor(15,25); display.println("Umiditate");
 display.drawRect(0,0,82,24,BLACK);
   display.drawRect(0,25,82,23,BLACK);
 display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(BLACK,WHITE); // 'inverted' text
  display.setTextSize(1);
  display.setCursor(1,20);
  display.println(event.temperature);
  display.setCursor(70,20);display.print("C");
  display.drawCircle(65,12,2,BLACK);
 //float h= dht.humidity().getEvent(&event);
  display.setCursor(1,45);display.println(event.relative_humidity);
  display.setCursor(65,45);display.print("%");
 display.setFont();
 
  display.display();
}


