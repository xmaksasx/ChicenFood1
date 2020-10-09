#include <Arduino.h>
#include <stdint.h>
#include "RTClib.h"
#include <LiquidCrystal_I2C.h>

unsigned long prevMillis = 0;       // Пройденное время с момента включения
unsigned long FoodInterval = 30000; // Время подачи корма

extern LiquidCrystal_I2C lcd;
extern DateTime DateTimeNow;
extern uint8_t relayFoodLeft;  // Реле 1
extern uint8_t relayFoodRight; // Реле 2

struct TimesFood
{
    uint8_t hour;
    bool stateRelayLeft;
    bool stateRelayRight;
};

/// Времена включения кормушек
TimesFood TimesFood3[] = {{8, true, true}, {16, true, true}, {0, true, true}};
TimesFood TimesFood4[] = {{6, true, true}, {12, true, true}, {18, true, true}, {23, true, true}};
TimesFood TimesFood5[] = {{6, true, true}, {11, true, true}, {16, true, true}, {21, true, true}, {1, true, true}};
TimesFood TimesFood6[] = {{6, true, true}, {10, true, true}, {14, true, true}, {18, true, true}, {22, true, true}, {2, true, true}};
//////////////////////////////////////

/// Тест релейвых модулей
extern int timeTest; // Время прохождения ленты по всей кормушки
const long interval = 1000;
extern unsigned long previousMillis;
//////////////////////////////////////