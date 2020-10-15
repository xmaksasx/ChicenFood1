#include "EnergisingVentilationRelay.h"

void WorkVentilationRelay(int VentilationTime[], int arraySize)
{
    for (uint8_t i = 0; i < arraySize; i++)
    {
        if (DateTimeNow.hour() == VentilationTime[i] && DateTimeNow.minute() == 30)
            digitalWrite(relayVentilation,LOW );
        if (DateTimeNow.hour() == VentilationTime[i] && DateTimeNow.minute() > 35)
            digitalWrite(relayVentilation, HIGH);
    }
}

void StartVentilating(int idx)
{
    switch (idx)
    {
    case 4:
        WorkVentilationRelay(VentilationTime4, sizeof(VentilationTime4) / sizeof(int));
        break;
    case 7:
        WorkVentilationRelay(VentilationTime7, sizeof(VentilationTime7) / sizeof(int));
        break;
    case 10:
        WorkVentilationRelay(VentilationTime10, sizeof(VentilationTime10) / sizeof(int));
        break;
    default:
        break;
    }
}

void StartTestVentilating(uint8_t mode)
{
    lcd.setCursor(0, 1);
    lcd.print("Test Vent - ");
    lcd.setCursor(12, 1);
    digitalWrite(relayVentilation, !mode);
    if (mode == 1)
        lcd.print("ON ");
    else
        lcd.print("OFF");
}
