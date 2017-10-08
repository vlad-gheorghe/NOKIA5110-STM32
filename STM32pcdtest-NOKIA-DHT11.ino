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
// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
//Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

// Hardware SPI (faster, but must use certain hardware pins):
// SCK is LCD serial clock (SCLK) - this is pin 13 on Arduino Uno
// MOSI is LCD DIN - this is pin 11 on an Arduino Uno
// pin 5 - Data/Command select (D/C)
// pin 15 - LCD chip select (CS)
// pin 4 - LCD reset (RST)
//Adafruit_PCD8544 display = Adafruit_PCD8544(PB13,PB12,PB3,PB5,PB4);
// Note with hardware SPI MISO and SS pins aren't used but will still be read
// and written to during SPI transfer.  Be careful sharing these pins!

/******************************************************************
ESP8266 with PCD8544 display

== Parts ==

* Adafruit Huzzah ESP8266 https://www.adafruit.com/products/2471

* Adafruit PCD8544/5110 display https://www.adafruit.com/product/338

* Adafruit USB to TTL serial cable https://www.adafruit.com/products/954

== Connection ==

USB TTL     Huzzah      Nokia 5110  Description
            ESP8266     PCD8544

            GND         GND         Ground
            3V          VCC         3.3V from Huzzah to display
            14          CLK         Output from ESP SPI clock
            13          DIN         Output from ESP SPI MOSI to display data input
            12          D/C         Output from display data/command to ESP
            #5          CS          Output from ESP to chip select/enable display
            #4          RST         Output from ESP to reset display
                        LED         3.3V to turn backlight on

GND (blk)   GND                     Ground
5V  (red)   V+                      5V power from PC or charger
TX  (green) RX                      Serial data from IDE to ESP
RX  (white) TX                      Serial data to ESP from IDE
******************************************************************/

// ESP8266 Software SPI (slower updates, more flexible pin options):
// pin 14 - Serial clock out (SCLK)
// pin 13 - Serial data out (DIN)
// pin 12 - Data/Command select (D/C)
// pin 5 - LCD chip select (CS)
// pin 4 - LCD reset (RST)
//Adafruit_PCD8544 display = Adafruit_PCD8544(14, 13, 12, 5, 4);

// If using an ESP8266, use this option. Comment out the other options.
// ESP8266 Hardware SPI (faster, but must use certain hardware pins):
// SCK is LCD serial clock (SCLK) - this is pin 14 on Huzzah ESP8266
// MOSI is LCD DIN - this is pin 13 on an Huzzah ESP8266
// pin 12 - Data/Command select (D/C) on an Huzzah ESP8266
// pin 5 - LCD chip select (CS)
// pin 4 - LCD reset (RST)
//Adafruit_PCD8544 display = Adafruit_PCD8544(12, 5, 4);

// ESP32 hardware-SPI
// pin 17 - Data/Command select (D/C)
// pin 5 - LCD chip select (CS)
// pin 16 - LCD reset (RST)
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
 float h= dht.humidity().getEvent(&event);
  display.setCursor(1,45);display.println(event.relative_humidity);
  display.setCursor(65,45);display.print("%");
 display.setFont();
 
  display.display();
}


