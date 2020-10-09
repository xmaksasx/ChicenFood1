#include "EnergisingLightRelay.h"

void WorkLightRelay()
{
    if (DateTimeNow.hour() == lightingOff)
        digitalWrite(relayLight, LOW);
    if (DateTimeNow.hour() == lightingOn)
        digitalWrite(relayLight, HIGH);
}

void StartLighting()
{
    WorkLightRelay();
}

void StartTestLight(uint8_t mode)
{
    lcd.setCursor(0, 1);
    lcd.print("Test Light - ");
    lcd.setCursor(13, 1);
    digitalWrite(relayLight, !mode);
    if (mode == 1)
        lcd.print("ON ");
    else
        lcd.print("OFF");
}