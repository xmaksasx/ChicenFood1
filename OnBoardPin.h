#include <stdint.h>
#include "RTClib.h"
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include <EEPROM.h>


#define DHTPIN 39
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void StartVentilating(int idx);
void StartFeeding(int idx);
void StartTestVentilating(uint8_t mode);
void StartTestLight(uint8_t mode);
void StartTestFood(uint8_t mode, uint8_t relay);
void StartLighting();

/// Пины на плате
uint8_t nextMenuBtn = 4; // Главная кнопка
uint8_t btn1 = 37;       // Кнопка 1
uint8_t btn2 = 6;        // Кнопка 2
uint8_t btn3 = 12;       // Кнопка 3

uint8_t relayLight = 27;       // Реле освещения
uint8_t relayVentilation = 11; // Реле вентиляции
uint8_t relayHotLight = 23;    // Реле горячего освещения
uint8_t relayReserve = 9;      // Реле запасное

uint8_t relayFoodLeft = 25; // Реле левой кормушки
uint8_t relayFoodRight = 7; // Реле правой кормушки
//////////////////////////////////////

/// Объект rtc для работы с часами реально времени
RTC_DS3231 rtc;
DateTime DateTimeNow;
//////////////////////////////////////

/// Объект lcd для работы с дисплеем
LiquidCrystal_I2C lcd(0x27, 20, 4);
//////////////////////////////////////

/// Меню и подменю
uint8_t curMenu = 1;    // Номер дисплея(условного дислея, в роли дисплея выступают функции с названиями "SHOW" вначале функции)
uint8_t curSubMenu = 1; // Номер дисплея(условного дислея, в роли дисплея выступают функции с названиями "SHOW" вначале функции)
//////////////////////////////////////

/// Настройри включения реле
uint8_t period = 3;   // Количество квлючения реле
uint8_t duration = 5; // Продолжительность включения реле
//////////////////////////////////////

uint8_t FeedingMode = 3;
uint8_t VentilationMode = 7;

unsigned long previousMillis = 0;
int timeTest = 0;
