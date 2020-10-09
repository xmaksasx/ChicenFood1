#include <Arduino.h>
#include <stdint.h>
#include "RTClib.h"
#include <LiquidCrystal_I2C.h>

int lightingOff = 3;
int lightingOn = 5;

extern LiquidCrystal_I2C lcd;
extern uint8_t relayLight;     // Реле освещения
extern DateTime DateTimeNow;