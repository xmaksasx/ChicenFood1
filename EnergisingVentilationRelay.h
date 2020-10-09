#include <Arduino.h>
#include <stdint.h>
#include "RTClib.h"
#include <LiquidCrystal_I2C.h>

int VentilationTime4[] = {6, 12, 18, 23};
int VentilationTime7[] = {2, 6, 10, 12, 16, 20, 23};
int VentilationTime10[] = {2, 6, 8, 10, 12, 14, 16, 18, 20, 22};

extern LiquidCrystal_I2C lcd;
extern uint8_t relayVentilation;
extern DateTime DateTimeNow;
