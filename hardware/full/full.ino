#include <EEPROM.h>
#include "GravityTDS.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2
#define TdsSensorPin A0
LiquidCrystal_I2C lcd(0x27,20,4);
GravityTDS gravityTds;
OneWire oneWire(ONE_WIRE_BUS);  
DallasTemperature sensors(&oneWire);
#define green 6
#define red 7
#define buzzer 8
float temperature = 0,tdsValue = 0;
 
void setup()
{
    Serial.begin(9600);
    sensors.begin();
    lcd.init();                      // initialize the lcd 
    lcd.init();
    // Print a message to the LCD.
    lcd.backlight();
    pinMode(green,OUTPUT);
    pinMode(red,OUTPUT);
    pinMode(buzzer,OUTPUT);
    gravityTds.setPin(TdsSensorPin);
    gravityTds.setAref(5.0);  //reference voltage on ADC, default 5.0V on Arduino UNO
    gravityTds.setAdcRange(1024);  //1024 for 10bit ADC;4096 for 12bit ADC
    gravityTds.begin();  //initialization
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Water quality");
    lcd.setCursor(0,1);
    lcd.print("monitoring");
    digitalWrite(green, HIGH);
    delay(3000);
}
 
void loop()
{
    sensors.requestTemperatures();
    gravityTds.setTemperature(temperature);  // set the temperature and execute temperature compensation
    gravityTds.update();  //sample and calculate
    sensors.getTempCByIndex(0);
    tdsValue = gravityTds.getTdsValue();  // then get the value
    //Serial.println((String)"temp="+sensors.getTempCByIndex(0)+"&ppm="+tdsValue);
    Serial.println((String)"{'temp':'" + sensors.getTempCByIndex(0) + "', 'ppm':" + tdsValue + "}");
    if(tdsValue>600){
      lowq();
      } else{
      goodq();
      }
}
void goodq(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Good quality");
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(sensors.getTempCByIndex(0));
  lcd.print(" C");
  digitalWrite(green, HIGH);
  digitalWrite(red, LOW);
  delay(2000);
  }
void lowq(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Low quality");
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(sensors.getTempCByIndex(0));
  lcd.print(" C");
  digitalWrite(green, LOW);
  digitalWrite(red, HIGH);
  tone(buzzer, 1000, 500);
  delay(2000);
  }
