#include "U8glib.h"
#include "onBoardPin.h"

void setup()
{
  Serial.begin(9600);
  Serial.print("nextMenuBtn ");
  Serial.println(nextMenuBtn);

  dht.begin();

  lcd.init();
  lcd.backlight();

  FeedingMode = EEPROM.read(0);
  VentilationMode = EEPROM.read(1);
  if (FeedingMode < 3 || FeedingMode > 6)
    FeedingMode = 3;
  if (VentilationMode < 4 || FeedingMode > 11)
    VentilationMode = 4;

  pinMode(nextMenuBtn, INPUT);
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);

  pinMode(relayLight, OUTPUT);
  pinMode(relayVentilation, OUTPUT);
  pinMode(relayHotLight, OUTPUT);
  pinMode(relayReserve, OUTPUT);
  pinMode(relayFoodLeft, OUTPUT);
  pinMode(relayFoodRight, OUTPUT);

  digitalWrite(relayLight, HIGH);
  digitalWrite(relayVentilation, HIGH);
  digitalWrite(relayHotLight, HIGH);
  digitalWrite(relayReserve, HIGH);
  digitalWrite(relayFoodLeft, HIGH);
  digitalWrite(relayFoodRight, HIGH);

  if (!rtc.begin())
  {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  //rtc.adjust(DateTime((__DATE__), (__TIME__)));
}

void loop()
{
  DateTimeNow = rtc.now();
  switch (ReadBtn())
  {
  case 1:
    ShowTime();
    break;
  case 2:
    ShowSettings();
    break;
  case 3:
    ShowTest();
    break;
  default:
    break;
  }
  StartFeeding(FeedingMode);
  StartVentilating(VentilationMode);
  StartLighting();
  delay(100);
}

void ShowTime(void)
{

  int hour = DateTimeNow.hour();
  int minute = DateTimeNow.minute();
  int sec = DateTimeNow.second();

  if (hour < 10)
  {
    lcd.setCursor(4, 0);
    lcd.print("0");
    lcd.setCursor(5, 0);
    lcd.print(hour);
  }
  else
  {
    lcd.setCursor(4, 0);
    lcd.print(hour);
  }

  lcd.setCursor(6, 0);
  lcd.print(":");

  if (minute < 10)
  {
    lcd.setCursor(7, 0);
    lcd.print("0");
    lcd.setCursor(8, 0);
    lcd.print(minute);
  }
  else
  {
    lcd.setCursor(7, 0);
    lcd.print(minute);
  }

  lcd.setCursor(9, 0);
  lcd.print(":");

  if (sec < 10)
  {
    lcd.setCursor(10, 0);
    lcd.print("0");
    lcd.setCursor(11, 0);
    lcd.print(sec);
  }
  else
  {
    lcd.setCursor(10, 0);
    lcd.print(sec);
  }

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (!isnan(h) || !isnan(t))
  {
    lcd.setCursor(1, 1);
    lcd.print("t");
    lcd.setCursor(2, 1);
    lcd.print(t);

    lcd.setCursor(9, 1);
    lcd.print("h");
    lcd.setCursor(10, 1);
    lcd.print(h);
  }
}

void ShowSettings()
{
  lcd.setCursor(1, 0);
  lcd.print("Hello Settings");
  switch (curSubMenu)
  {
  case 1:
  {
    lcd.setCursor(0, 1);
    lcd.print("Count Food - ");
    lcd.setCursor(13, 1);
    lcd.print(FeedingMode);
    uint8_t _btnt = digitalRead(btn2);
    if (_btnt == 1)
    {
      FeedingMode++;
      if (FeedingMode > 6)
        FeedingMode = 3;
      delay(150);
    }
    uint8_t set = digitalRead(btn3);
    if (set == 1)
    {
      EEPROM.write(0, FeedingMode);
      delay(300);
    }
  }
  break;
  case 2:
  {
    lcd.setCursor(0, 1);
    lcd.print("Count Vent - ");
    lcd.setCursor(13, 1);
    lcd.print(VentilationMode);
    uint8_t _btnt = digitalRead(btn2);
    if (_btnt == 1)
    {
      lcd.clear();
      VentilationMode = VentilationMode + 3;
      if (VentilationMode > 10)
        VentilationMode = 4;
      delay(150);
    }
    uint8_t set = digitalRead(btn3);
    if (set == 1)
    {
      EEPROM.write(1, VentilationMode);
      delay(300);
    }
  }
  break;
  case 3:
    lcd.setCursor(0, 1);
    lcd.print("Nothing 1 ");
    break;

  case 4:
    lcd.setCursor(0, 1);
    lcd.print("Nothing 2 ");
    break;

  default:
    break;
  }
}

void ShowTest()
{
  lcd.setCursor(3, 0);
  lcd.print("Hello Test");
  switch (curSubMenu)
  {
  case 1:
  {
    uint8_t _btnt = digitalRead(btn2);
    StartTestFood(_btnt, relayFoodLeft);
  }
  break;
  case 2:
  {
    uint8_t _btnt = digitalRead(btn2);
    StartTestFood(_btnt, relayFoodRight);
  }
  break;
  case 3:
  {
    uint8_t _btnt = digitalRead(btn2);
    StartTestVentilating(_btnt);
  }
  break;
  case 4:
  {
    uint8_t _btnt = digitalRead(btn2);
    StartTestLight(_btnt);
  }
  break;
  default:
    break;
  }
}

int ReadBtn(void)
{
  // считывание кнопок
  uint8_t _nextMenu = digitalRead(nextMenuBtn);
  uint8_t _btn1 = digitalRead(btn1);
  uint8_t _btn2 = digitalRead(btn2);

  ////////////////////// СОСТОЯНИЕ ГЛАВНОГО ДИСПЛЕЯ //////////////////////
  if (_nextMenu == 1)
  {
    lcd.clear();
    curMenu++;
    if (curMenu > 3)
      curMenu = 1;
    curSubMenu = 1;
    delay(200);
  }

  if (_btn1 == 1)
  {
    lcd.clear();
    previousMillis = 0;
    timeTest = 0;
    curSubMenu++;
    if (curSubMenu > 4)
      curSubMenu = 1;
    delay(200);
  }

  return (int)curMenu;
  ////////////////////// СОСТОЯНИЕ ГЛАВНОГО ДИСПЛЕЯ //////////////////////
}
