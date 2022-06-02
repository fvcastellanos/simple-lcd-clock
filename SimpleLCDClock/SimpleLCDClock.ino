#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal.h>

// Constant definition
const int RS = 12, EN = 11, D4 = 5, D5 = 4, D6 = 3, D7 = 2;

// Object instantiation
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
RTC_DS3231 rtc;

// Global variables
char daysOfTheWeek[7][12] = {"DO", "LU", "MA", "MI", "JU", "VI", "SA"};

void setup () 
{
  // Configure serial console
  Serial.begin(9600);
  delay(200);
  
  // Configure LCD
  configureLCD();

  // Configure RTC
  configureRTC();
}

void loop () 
{
  displayDateTime(rtc.now());
  delay(1000);
}

// ---------------------------------------------------------------------------

void configureLCD() {

  lcd.begin(16, 2);
  lcd.print("Reloj NANO");
  lcd.setCursor(0,1);
  lcd.print("v. 1.0");
  delay(2000);  
}

// ---------------------------------------------------------------------------

void configureRTC() {

  if (!rtc.begin()) {

    lcd.setCursor(0,0);
    lcd.print("RTC not found");
    lcd.setCursor(0,1);
    lcd.print("Nothing to do...");
    while (1);
  }

  if (rtc.lostPower()) {

    lcd.setCursor(0,0);
    lcd.print("RTC lost power");
    lcd.setCursor(0,1);
    lcd.print("Set time using serial");
  
  // Comment out below lines once you set the date & time.
    // Following line sets the RTC to the date & time this sketch was compiled
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  
    // Following line sets the RTC with an explicit date & time
    // for example to set January 27 2017 at 12:56 you would call:
    // rtc.adjust(DateTime(2017, 1, 27, 12, 56, 0));
  }  
}

// ---------------------------------------------------------------------------

void displayDateTime(DateTime now) {

  lcd.clear();
  displayDate(now);    
  displayTime(now);    
}

void displayDate(DateTime now) {

  int day = now.day();
  int month = now.month();

  String dayText = day < 10 ? "0" + String(day) 
    : String(day);

  String monthText = month < 10 ? "0" + String(month)
    : String(month);

  lcd.setCursor(3,0);
  lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
  lcd.setCursor(6,0);
  lcd.print(dayText);
  lcd.setCursor(8,0);
  lcd.print('/');
  lcd.setCursor(9,0);
  lcd.print(monthText);
  lcd.setCursor(11,0);
  lcd.print('/');
  lcd.setCursor(12,0);
  lcd.print(now.year(), DEC);
}

void displayTime(DateTime now) {

  int hour = now.hour();
  int minute = now.minute();
  int second = now.second();

  String hourText = hour < 10 ? "0" + String(hour)
    : String(hour);

  String minuteText = minute < 10 ? "0" + String(minute)
    : String(minute);

  String secondText = second < 10 ? "0" + String(second)
    : String(second);

  lcd.setCursor(8,1);
  lcd.print(hourText);
  lcd.setCursor(10,1);
  lcd.print(':');
  lcd.setCursor(11,1);
  lcd.print(minuteText);
  lcd.setCursor(13,1);
  lcd.print(':');
  lcd.setCursor(14,1);
  lcd.print(secondText);
}
