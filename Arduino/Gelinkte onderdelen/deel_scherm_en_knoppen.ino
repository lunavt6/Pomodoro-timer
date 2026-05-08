#include <LiquidCrystal.h>
int WaardeKnop1;
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, e = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, e, d4, d5, d6, d7);
int AanUit = 7;
int Toestand;
int VorigeKnop1;

int knop1 = 6;
int knop2 = 8;
int knop3 = 10;
int knop4 = 13;

unsigned long laatsteDruk1;

int WaardeKnop2;
int VorigeKnop2;
int WaardeKnop3;
int VorigeKnop3;
int waarde = 0;
int minuten = 00;
int seconden = 00;

int WaardeKnop4;
int VorigeKnop4;
int i;
int j;

bool timerLoopt = false;

unsigned long laatstetijd = 0;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
unsigned long lastDebounceTime4;

void setup()
{
  // set up the LCD's number of columns and rows:
  pinMode(knop1, INPUT_PULLUP);
  pinMode(knop2, INPUT_PULLUP);
  pinMode(knop3, INPUT_PULLUP);
  pinMode(knop4, INPUT_PULLUP);
  pinMode(AanUit, OUTPUT);
  digitalWrite(7, LOW);
  Toestand = 0;
  lcd.begin(16, 2);
  VorigeKnop1 = HIGH;
  VorigeKnop2 = HIGH;
  VorigeKnop3 = HIGH;
  VorigeKnop4 = HIGH;
  Serial.begin(9600);
}

void loop()
{
  // knop 1: aan/uit
  WaardeKnop1 = digitalRead(knop1);

  if (WaardeKnop1 == LOW and VorigeKnop1 == HIGH)
  {

    if (millis() - laatsteDruk1 > 200)
    {

      Toestand = !Toestand;
      laatsteDruk1 = millis();

      if (Toestand == 1)
      {
        digitalWrite(AanUit, HIGH);
        lcd.display();
        lcd.clear();
        lcd.print("Tijd instellen");
      }
      else
      {
        digitalWrite(AanUit, LOW);
        nodisplay();
      }
    }
  }
  VorigeKnop1 = WaardeKnop1;
  // knop 2 en 3: tijd verhogen en verlagen
  // put your main code here, to run repeatedly:
  int reading_H = digitalRead(knop2);
  int reading_L = digitalRead(knop3);

  if (reading_H != VorigeKnop2)
  {
    lastDebounceTime = millis();
  }

  if (reading_L != VorigeKnop3)
  {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    if (reading_H != WaardeKnop2)
    {
      WaardeKnop2 = reading_H;
      if (WaardeKnop2 == LOW)
      {
        waarde++;
        if (waarde % 2 == 0)
        {
          minuten = waarde / 2;
          seconden = 0;
        }
        if (waarde % 2 == 1)
        {
          minuten = waarde / 2;
          seconden = 30;
        }
      }
    }
  }

  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    if (reading_L != WaardeKnop3)
    {
      WaardeKnop3 = reading_L;
      if (WaardeKnop3 == LOW)
      {
        waarde--;
        if (waarde % 2 == 0)
        {
          minuten = waarde / 2;
          seconden = 0;
        }
        if (waarde % 2 == 1)
        {
          minuten = waarde / 2;
          seconden = 30;
        }
      }
    }
  }

  Serial.print("waarde = ");
  Serial.print(waarde);
  Serial.print(", minuten=");
  Serial.print(minuten);
  Serial.print(", seconden=");
  Serial.println(seconden);

  // knop 4: tijd start met lopen

  VorigeKnop2 = reading_H;
  VorigeKnop3 = reading_L;

  WaardeKnop4 = digitalRead(knop4);

  if (WaardeKnop4 == LOW and VorigeKnop4 == HIGH)
  {
    if (millis() - lastDebounceTime4 > debounceDelay)
    {

      timerLoopt = !timerLoopt;

      lastDebounceTime4 = millis();

      if (timerLoopt)
      {
        i = minuten;
        j = seconden;
        laatstetijd = millis();
      }
    }
  }
  VorigeKnop4 = WaardeKnop4;
  if (timerLoopt)
  {
    if (millis() - laatstetijd >= 1000)
    {
      laatstetijd = millis();

      j--;

      if (j < 0)
      {
        j = 59;
        i--;
      }

      if (i < 0)
      {
        i = 0;
        j = 0;
        timerLoopt = false;
      }
    }
  }

  lcd.setCursor(0, 1);

  if (timerLoopt)
  {
    lcd.print(i);
    lcd.print(":");
    if (j < 10)
    {
      lcd.print("0");
    }
    lcd.print(j);
  }
  else
  {
    lcd.print(minuten);
    lcd.print(":");
    if (seconden < 10)
    {
      lcd.print("0");
    }
    lcd.print(seconden);
  }
}
