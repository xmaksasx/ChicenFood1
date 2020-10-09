#include "EnergisingFoodRelay.h"

void WorkMillis(uint8_t relay, bool *state)
{
    unsigned long currentMillis = millis();
    if (currentMillis - prevMillis >= FoodInterval)
    {
        prevMillis = currentMillis;
        int relayState = !digitalRead(relay);
        digitalWrite(relay, relayState);
        if (relayState == HIGH)
        {
            *state = false;
            prevMillis = 0;
        }
    }
}

void WorkFoodRelay(TimesFood timesFood[], int arraySize)
{

    for (uint8_t i = 0; i < arraySize; i++)
    {

        if ((DateTimeNow.hour() == timesFood[i].hour && DateTimeNow.minute() > 15 && DateTimeNow.minute() < 20) && timesFood[i].stateRelayLeft)
        {
            Serial.print(DateTimeNow.hour());
            Serial.print("  ");
            Serial.print(DateTimeNow.minute());
            Serial.print("  ");
            Serial.println(timesFood[i].stateRelayLeft);

            WorkMillis(relayFoodLeft, &timesFood[i].stateRelayLeft);
        }

        if ((DateTimeNow.hour() == timesFood[i].hour && DateTimeNow.minute() > 25 && DateTimeNow.minute() < 30) && timesFood[i].stateRelayRight)
        {
            Serial.print(DateTimeNow.hour());
            Serial.print("  ");
            Serial.print(DateTimeNow.minute());
            Serial.print("  ");
            Serial.println(timesFood[i].stateRelayRight);
            WorkMillis(relayFoodRight, &timesFood[i].stateRelayRight);
        }
    }

    for (uint8_t i = 0; i < arraySize; i++)
    {
        if (DateTimeNow.hour() != timesFood[i].hour)
        {
            timesFood[i].stateRelayLeft = true;
            timesFood[i].stateRelayRight = true;
        }
    }
}

void StartFeeding(int idx)
{

    switch (idx)
    {
    case 3:

        WorkFoodRelay(TimesFood3, sizeof(TimesFood3) / sizeof(TimesFood));
        break;
    case 4:
        WorkFoodRelay(TimesFood4, sizeof(TimesFood4) / sizeof(TimesFood));
        break;
    case 5:
        WorkFoodRelay(TimesFood5, sizeof(TimesFood5) / sizeof(TimesFood));
        break;
    case 6:
        WorkFoodRelay(TimesFood6, sizeof(TimesFood6) / sizeof(TimesFood));
        break;
    default:
        break;
    }
}

void TestTime(int *timeTest, uint8_t pin, uint8_t mode)
{

    if (mode)
    {
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis >= interval)
        {
            previousMillis = currentMillis;
            (*timeTest)++;
        }
        digitalWrite(pin, LOW);
    }
    else
    {
        digitalWrite(pin, HIGH);
    }
}

void StartTestFood(uint8_t mode, uint8_t relay)
{
    lcd.setCursor(0, 1);
    if (relay == 25)
    {
        lcd.print("Test Left - ");
        lcd.setCursor(12, 1);
    }
    else
    {
        lcd.print("Test Right - ");
        lcd.setCursor(13, 1);
    }

    TestTime(&timeTest, relay, mode);
    lcd.print(timeTest);
}