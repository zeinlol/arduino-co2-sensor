/***************************************************************************
  This is a library for the CCS811 air

  This sketch reads the sensor

  Designed specifically to work with the Adafruit CCS811 breakout
  ----> http://www.adafruit.com/products/3566

  These sensors use I2C to communicate. The device's I2C address is 0x5A

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Dean Miller for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include "Adafruit_CCS811.h"
#include "Wire.h"
#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x27);  // set the LCD address to 0x27 for a 16 chars and 2 line display

Adafruit_CCS811 ccs;

void setup() {

  //LCD SETINGS & STARTUP
  
  lcd.begin(8, 2);
  lcd.setBacklight(255);
  // Print a message to the LCD.
  lcd.clear();
  // lcd.setCursor(0, 0); чисто для наглядности
  lcd.print("CO2 Sens");
  lcd.setCursor(0, 1);
  lcd.print("or. boot");
  delay(2000);

  //CCS811 monitoring
  
  Serial.begin(9600);

  Serial.println("CCS811 test");

  ccs.begin();
  if(!ccs.begin()){
    Serial.println("Failed to start sensor! Please check your wiring.");
    lcd.setCursor(0, 0);
    lcd.print("Failed t");
    lcd.setCursor(0, 1);
    lcd.print("o start!");
    while(1);
  }
  // Wait for the sensor to be ready
  //while(!ccs.available());
}

void loop() {
  if(ccs.available()){
    if(!ccs.readData()){

      //for debuging  ccs811
      Serial.print("CO2: ");
      Serial.print(ccs.geteCO2());
      Serial.print("ppm, TVOC: ");
      Serial.print(ccs.getTVOC());
      Serial.println("ppb ");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("CO2:");
      lcd.setCursor(4, 0);
      lcd.print(ccs.geteCO2());
      lcd.setCursor(0, 1);
      lcd.print("TVOC:");
      lcd.setCursor(5, 1);
      lcd.print(ccs.getTVOC());
    }
    else{
      Serial.println("ERROR!");
      lcd.setCursor(0, 0);
      lcd.print("SENSOR");
      lcd.setCursor(0, 1);
      lcd.print("ERROR!");
      while(1);
    }
  }
  delay(500);
}
