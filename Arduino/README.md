# Codes arduino
> Deze codes werden nadat de finale code werd gemaakt in deze README geplaatst aangezien er niet kon klinkt worden naar '.io' bestanden. Deze bestanden zijn echter wel terug te vinden in deze map. In deze '.io' bestanden werd bij elke iteratie van dit proces de code geüpdated.

## Aparte componenten
- [Buzzer](./Aparte%20onderdelen/deel_geluid.ino)
```cpp
int speaker = 4;


void setup() {
  // put your setup code here, to run once:
  pinMode(speaker, OUTPUT);
  Serial.begin(9600);
  Serial.println("gelukt");
}

void loop() {
  // put your main code here, to run repeatedly:
  tone(speaker, 262, 100); // frequentie = 262, tijd = 0.1 s
  delay(5000); // 5 seconden tussen elke beep
  //noTone(speaker); -> geen idee wat dit doet, hoor geen verschil met of zonder
}
```
- [Knoppen](<Aparte onderdelen/deel_knoppen.ino>)
```cpp
const int buttonPin_H = 2;
const int buttonPin_L = 4;
// Hoger is blauwe button
// Lager is groene button

int buttonState_H;
int lastButtonState_H = LOW;
int buttonState_L;
int lastButtonState_L = LOW;
int waarde = 0;
int uur = 00;
int minuten = 00;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup()
{
    pinMode(buttonPin_H, INPUT);
    pinMode(buttonPin_L, INPUT);

    // put your setup code here, to run once:
    Serial.begin(9600);
}

void loop()
{
    // put your main code here, to run repeatedly:
    int reading_H = digitalRead(buttonPin_H);
    int reading_L = digitalRead(buttonPin_L);

    if (reading_H != lastButtonState_H)
    {
        lastDebounceTime = millis();
    }

    if (reading_L != lastButtonState_L)
    {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay)
    {
        if (reading_H != buttonState_H)
        {
            buttonState_H = reading_H;
            if (buttonState_H == HIGH)
            {
                waarde++;
                if (waarde % 2 == 0)
                {
                    uur = waarde / 2;
                    minuten = 0;
                }
                if (waarde % 2 == 1)
                {
                    uur = waarde / 2;
                    minuten = 30;
                }
            }
        }
    }

    if ((millis() - lastDebounceTime) > debounceDelay)
    {
        if (reading_L != buttonState_L)
        {
            buttonState_L = reading_L;
            if (buttonState_L == HIGH)
            {
                waarde--;
                if (waarde % 2 == 0)
                {
                    uur = waarde / 2;
                    minuten = 0;
                }
                if (waarde % 2 == 1)
                {
                    uur = waarde / 2;
                    minuten = 30;
                }
            }
        }
    }

    Serial.print("waarde = ");
    Serial.print(waarde);
    Serial.print(",uur=");
    Serial.print(uur);
    Serial.print(",,minuten=");
    Serial.println(minuten);

    lastButtonState_H = reading_H;
    lastButtonState_L = reading_L;
}
```
- [LED's](<Aparte onderdelen/deel_leds.ino>)
```cpp
// statemachine gebruiken omdat de lichten na elkaar moeten afgaan, niet tegelijk

int ledPinR = 3;
int ledPinG = 4;

unsigned long vorigeTijd;

enum LedStates {
  LED_UIT_G_LED_UIT_R,
  LED_AAN_G_LED_UIT_R,
  LED_UIT_G_LED_AAN_R
};

LedStates ledState = LED_UIT_G_LED_UIT_R; // toestel staat uit

void setup() {
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinG, OUTPUT);
  Serial.begin(115200);
  vorigeTijd = millis();
  Serial.begin(9600);
}

void loop() {
  Serial.println("gelukt");
  
  // verschillende tijden per state
  unsigned long interval;
  
  switch (ledState) {
    case LED_UIT_G_LED_UIT_R:
      interval = 1000; // 1 sec
      break;

    case LED_AAN_G_LED_UIT_R:
      interval = 5000; // 5 sec groen
      break;

    case LED_UIT_G_LED_AAN_R:
      interval = 1000; // 1 sec rood
      break;
  }
  
  // state wisselen  
  if (millis() - vorigeTijd >= interval) {
    vorigeTijd = millis();

    if (ledState == LED_UIT_G_LED_UIT_R){ //toestel uit -> studeertijd
      ledState = LED_AAN_G_LED_UIT_R;
    }
    else if (ledState == LED_AAN_G_LED_UIT_R) { // studeertijd -> pauze
      ledState = LED_UIT_G_LED_AAN_R;
    }
    else // pauze -> uit
      ledState = LED_UIT_G_LED_UIT_R;
    }

    Serial.print("Nieuwe state: ");
    Serial.println(ledState);

  // state gedrag
  switch (ledState) {
    
    case LED_UIT_G_LED_UIT_R: // achter de schermen 0
      digitalWrite(ledPinG, LOW);
      digitalWrite(ledPinR, LOW);
      break;
    
    case LED_AAN_G_LED_UIT_R: // achter de schermen 1
      digitalWrite(ledPinG, HIGH);
      break;
    
    case LED_UIT_G_LED_AAN_R: // achter de schermen 2
      digitalWrite(ledPinG, LOW);
      digitalWrite(ledPinR, HIGH);
      break;
  }
}

```
- [Scherm](<Aparte onderdelen/deel_scherm.ino>)
```cpp
// include the library code:
#include <LiquidCrystal.h>
int WaardeKnop;
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, e = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, e, d4, d5, d6, d7);

// knop
int knop = 6;

void setup()
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Tijd instellen");
  pinMode(knop, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop()
{
  WaardeKnop = digitalRead(knop);
  if (WaardeKnop == LOW)
  {
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    // print the number of seconds since reset:
    lcd.setCursor(0, 1);
    lcd.print("                "); // leeg maken
    lcd.setCursor(0, 1);
    lcd.print(millis() / 1000);
  }
  Serial.println("gelukt");
}
```

## Samenvoegen componenten
- [Buzzer + LED's](<Gelinkte onderdelen/deel_geluid_en_LED.ino>)
```cpp
int speaker = 6;
int ledPinR = 3;
int ledPinG = 4;

unsigned long vorigeTijd;
unsigned long interval;

enum LedStates {
  LED_UIT_G_LED_UIT_R,
  LED_AAN_G_LED_UIT_R,
  LED_UIT_G_LED_AAN_R
};

LedStates ledState = LED_UIT_G_LED_UIT_R; // toestel staat uit

void setup() {
  // put your setup code here, to run once:
  pinMode(speaker, OUTPUT);
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinG, OUTPUT);
  Serial.begin(115200);
  vorigeTijd = millis();
  digitalWrite(ledPinG, LOW);
  digitalWrite(ledPinR, LOW);
}


void loop() {
  switch (ledState) {
    case LED_UIT_G_LED_UIT_R:
      interval = 1000; // 1 sec, werkt niet
      break;

    case LED_AAN_G_LED_UIT_R:
      interval = 5000; // 5 sec groen, werken
      break;

    case LED_UIT_G_LED_AAN_R:
      interval = 1000; // 1 sec rood, pauze
      break;
  }
  
  // state wisselen  
  if (millis() - vorigeTijd >= interval) {
    vorigeTijd = millis();

    if (ledState == LED_UIT_G_LED_UIT_R){ //toestel uit -> studeertijd
      tone(speaker, 262, 100);
      ledState = LED_AAN_G_LED_UIT_R;
      digitalWrite(ledPinG, HIGH);
      Serial.println("Nieuwe state: studeren ");

    }
    else if (ledState == LED_AAN_G_LED_UIT_R) { // studeertijd -> pauze
      tone(speaker, 262, 100);
      ledState = LED_UIT_G_LED_AAN_R;
      digitalWrite(ledPinG, LOW);
      digitalWrite(ledPinR, HIGH);
      Serial.println("Nieuwe state: pauze ");
    }
    else{ // pauze -> uit
      tone(speaker, 262, 100);
      ledState = LED_UIT_G_LED_UIT_R;
      digitalWrite(ledPinG, LOW);
      digitalWrite(ledPinR, LOW);
      Serial.println("Nieuwe state: uit");

    }
  }
}
```
- [Knoppen + Scherm](<Gelinkte onderdelen/deel_geluid_en_LED.ino>)
```cpp
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
```
## Finaal
- [Gehele werking](samenstelling_onderdelen/samenstelling_onderdelen.ino)
```cpp
// bibliotheek initialiseren nodig voor het LED-scherm
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Stel het aantal kolommen en rijen van het LCD-scherm in:
LiquidCrystal_I2C lcd(0x27, 16, 2);
int AanUit = 7; // voor 'A', om backlight aan en uit te zetten
int Toestand;

// variabelen nodig voor knoppen
int knop1 = 6;
int knop2 = 8;
int knop3 = 10;
int knop4 = 13;

unsigned long laatsteDruk1;
int WaardeKnop1;
int VorigeKnop1;
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

// variabelen nodig voor timer
bool timerLoopt = false;
unsigned long laatstetijd = 0;

// variabelen voor debounce, vloeiende werking
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
unsigned long lastDebounceTime4;

// variabelen nodig voor speaker
int speaker = 9;

// variabelen nodig voor Led's
int ledPinR = A1;
int ledPinG = A0;
unsigned long vorigeTijd;

enum LedStates
{
  LED_UIT_G_LED_UIT_R,
  LED_AAN_G_LED_UIT_R,
  LED_UIT_G_LED_AAN_R
};
LedStates vorigeState = LED_UIT_G_LED_UIT_R;
LedStates ledState = LED_UIT_G_LED_UIT_R; // toestel staat uit

// variabelen nodig voor pauze
int teller = 0;
int pauze = false;

// variabelen nodig voor 'studie' en 'studeren'
int studie = 0;
int studeren = 0;
int hoeveelPauze = 0;
int hoeveelPauzeMin = 0;
int hoeveelPauzeSec = 0;
int langePauze = 0;
int hoeveelStudieMin = 0;
int hoeveelStudieSec = 0;
int totaalPauzeSec = 0;

void setup()
{
  // PinModes output of input instellen
  pinMode(knop1, INPUT_PULLUP);
  pinMode(knop2, INPUT_PULLUP);
  pinMode(knop3, INPUT_PULLUP);
  pinMode(knop4, INPUT_PULLUP);
  pinMode(AanUit, OUTPUT);
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinG, OUTPUT);
  pinMode(speaker, OUTPUT);
  digitalWrite(7, LOW);
  // Initiële waarden goedzetten
  Toestand = 0;
  VorigeKnop1 = HIGH;
  VorigeKnop2 = HIGH;
  VorigeKnop3 = HIGH;
  VorigeKnop4 = HIGH;
  lcd.begin(16, 2);
  Serial.begin(9600);
  vorigeTijd = millis();
  digitalWrite(ledPinG, LOW);
  digitalWrite(ledPinR, LOW);
  lcd.init(); // LCD starten
}

void loop()
{
  // knop 1: aan/uit LCD-scherm code

  WaardeKnop1 = digitalRead(knop1);

  if (WaardeKnop1 == LOW and VorigeKnop1 == HIGH)
  { // nieuwe indrukking

    if (millis() - laatsteDruk1 > 200)
    { // debounce code

      Toestand = !Toestand; // om aan te duiden of scherm aan of uit moet
      laatsteDruk1 = millis();

      if (Toestand == 1)
      {
        lcd.backlight(); // backlight aanzetten
        digitalWrite(AanUit, HIGH);
        lcd.display(); // tekst aanzetten
        lcd.clear();   // zorgen dat er geen tekst staat
        lcd.print("Tijd instellen");
        lcd.setCursor(5, 1);
        lcd.print(" stud:");
      }
      else
      {
        lcd.noBacklight(); // backlight afzetten
        digitalWrite(AanUit, LOW);
        lcd.noDisplay(); // display uizetten
      }
    }
  }
  VorigeKnop1 = WaardeKnop1; // zodat de toestand niet constant verandert bij het binnenhalen van signalen

  // knop 2 en 3: tijd verhogen en verlagen

  int reading_H = digitalRead(knop2);
  int reading_L = digitalRead(knop3);

  if (reading_H != VorigeKnop2)
  { // knop 2 verandert van staat, ontvangt signaalverandering, pas als bounce lang genoeg gestopt 1 en die 1 signaal ontvangt wordt verder gegaan
    lastDebounceTime = millis();
  }

  if (reading_L != VorigeKnop3)
  { // knop 3 verandert van staat
    lastDebounceTime = millis();
  }
  // voor knop 2: optellen
  if ((millis() - lastDebounceTime) > debounceDelay)
  { // debounce, het lukt om status te veranderen, vertraging introduceren zodat bij eenmaal contact de status verandert
    if (reading_H != WaardeKnop2)
    {
      WaardeKnop2 = reading_H; // wordt geregistreerd zonder de bouce, anders zou volgende if meerder keren doorlopen worden
      if (WaardeKnop2 == LOW)
      {
        waarde++; // begint bij waarde 0, aan de hand van even of oneven zullen de minuten bepaald worden
        if (waarde % 2 == 0)
        { // waarde is even, bv. Waarde=2, is er 2 keer 30 seconden opgetelt dus 1 min
          minuten = waarde / 2;
          seconden = 0;
        }
        if (waarde % 2 == 1)
        { // waarde is oneven, bv 1, dus 1 keer 30 seconden
          minuten = waarde / 2;
          seconden = 30;
        }
      }
    }
  }
  // voor knop 3: aftrekken (zelfde als voorheen)
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
  VorigeKnop2 = reading_H; // om signaalverandering van signaal op te vangen
  VorigeKnop3 = reading_L;

  // knop 4: tijd start met lopen

  VorigeKnop2 = reading_H;
  VorigeKnop3 = reading_L;

  WaardeKnop4 = digitalRead(knop4);

  if (WaardeKnop4 == LOW and VorigeKnop4 == HIGH)
  {
    if (millis() - lastDebounceTime4 > debounceDelay)
    {                               // zelfde als voorheen: debounce
      timerLoopt = !timerLoopt;     // verandering in of timer moet aflopen of stoppen met aflopen wanneer knop ingeduwd wordt
      lastDebounceTime4 = millis(); // laatste indrukking knop

      if (timerLoopt)
      { // als de timer loop zijn de beginwaarden..
        i = minuten;
        j = seconden;
        laatstetijd = millis();
      }
    }
  }
  VorigeKnop4 = WaardeKnop4; // na doorlopen vorige code mag waarde aangepast worden

  // aftellende timer

  if (timerLoopt)
  {
    if (millis() - laatstetijd >= 1000)
    { // nadat 1 seconde verlopen is mag de seconde-waarde aangepast worden
      laatstetijd = millis();
      j--;

      if (j < 0)
      { // als j negatief wordt verminderen de min, en start een nieuwe minuut
        j = 59;
        i--;
      }

      if (j > 0 && j < 6 or j > 30 && j < 36)
      { // j moet gedurende deze intervallen pauze aangeven
        if (j == 5 or j == 35)
        { // op de led wisseling zal er een beep geluid te horen zijn
          tone(speaker, 262, 100);
          teller++;
        }
        pauze = true; // zal verderop ervoor zorgen dat het systeem zich in de state 'LED_UIT_G_LED_AAN_R' verkeert
      }
      if (j > 5 && j < 30 or j > 35 && j <= 59)
      {                // j moet gedurende deze intervallen studeren aangeven
        pauze = false; // zal verderop ervoor zorgen dat het systeem zich in de state 'LED_AAN_G_LED_UIT_R' verkeert
      }

      if (i < 0)
      { // als i vervolgens negatief wordt, stopt de timer
        i = 0;
        j = 0;
        timerLoopt = false;
        // teller++; // zal pauzeduur bepalen, na het stoppen van de timer is er een cyclus doorlopen
        pauze = false;           // zal verderop ervoor zorgen dat het systeem gedurende een tijd niets meer doet, deze variabele zorgt ervoor dat het systeem voor de eerste cyclus ook werkt
        tone(speaker, 262, 100); // wanneer de timer gedaan is weerklinkt een geluid om de gebruiker te alarmeren
      }
    }
  }
  // de tijd op het scherm printen

  lcd.setCursor(0, 1); // juiste plaats zetten waar tekst geprint zal worden

  if (digitalRead(AanUit) == HIGH)
  { // het backlight moet aanstaan, er moet dus op de aan/uit knop geduwd zijn om iets te printen op het scherm

    if (timerLoopt)
    { // als de timer loopt , wordt gewoon telkens de geüpdate tijd geprint
      if (i < 10)
      {
        lcd.print("0");
      }
      if (i < 0)
      {
        i = 0; // voor mooie tijden
      }
      lcd.print(i);
      lcd.print(":");
      if (j < 10)
        lcd.print("0"); // ervoor zorgen dat de minuten telkens met 2 cijfers worden weergegeven
      lcd.print(j);
    }
    else
    { // als de timer niet loopt, moeten gewoon de ingegeven waarden door knop2 en 3 weergegeven worden
      if (minuten < 10)
      {
        lcd.print("0");
      }
      if (minuten < 0)
      {
        minuten = 0; // voor mooie tijden
      }
      lcd.print(minuten);
      lcd.print(":");
      if (seconden < 10)
        lcd.print("0");
      lcd.print(seconden);
    }
  }

  else
  { // als het scherm niet aanstaat mag er ook geen tekst weergegeven worden
    lcd.clear();
  }

  // wanneer elke led zal branden of net niet

  // if(digitalRead(AanUit)==LOW){ // als het scherm niet aanstaat, mogen de led's ook nog niet branden -> niet nodig want zit in de else
  // ledState=LED_UIT_G_LED_UIT_R;
  //}
  if (timerLoopt)
  { // als de timer loopt en het scherm staat aan, dan is de groene led aan
    if (pauze == true)
    {
      ledState = LED_UIT_G_LED_AAN_R;
    }
    else
    {
      ledState = LED_AAN_G_LED_UIT_R;
    }
  }
  else
  { // als het scherm aanstaat en de timer niet loopt
    ledState = LED_UIT_G_LED_UIT_R;
  }

  // Leds laten branden, bij variabelen de juiste led's laten branden
  switch (ledState)
  {
  case LED_AAN_G_LED_UIT_R: // toestel uit -> studeertijd
    studie = 0;
    lcd.setCursor(0, 0);
    if (studeren == 0)
    { // variabele werd ingevoerd om zodat de text studeren niet knippert
      lcd.setCursor(0, 0);
      lcd.print("                         ");
      studeren++;
    }
    lcd.setCursor(0, 0);
    lcd.print("studeren");
    digitalWrite(ledPinG, HIGH);
    digitalWrite(ledPinR, LOW);
    lcd.setCursor(5, 1);       // juiste plaats zetten waar 'pauze' verwijderd moet worden
    lcd.print("            "); // 'pauze' verwijderen
    break;

  case LED_UIT_G_LED_AAN_R: // studeertijd -> pauze
    studeren = 0;
    digitalWrite(ledPinG, LOW);
    digitalWrite(ledPinR, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("                      ");
    lcd.setCursor(11, 1); // juiste plaats zetten waar 'pauze' geprint zal worden
    lcd.print("pauze");   // 'pauze' komt naast timer
    if (teller == 4)
    { // voor lange pauzes
      lcd.setCursor(11, 1);
      lcd.print("           ");
      lcd.setCursor(0, 1);
      lcd.print("lange pauze");
      delay(10000);
      teller = 0;
      lcd.setCursor(0, 1);
      lcd.print("           ");
      j = j - 10; // tijd loop door doorheen de pauze
      if (j < 0)
      {
        i--;
        j = 60 + j;
      }
    }
    break;

  case LED_UIT_G_LED_UIT_R:
    studeren = 0;
    digitalWrite(ledPinG, LOW);
    digitalWrite(ledPinR, LOW);
    if (digitalRead(AanUit) != LOW)
    {
      lcd.setCursor(0, 0);
      lcd.print("Tijd instellen");
      if (studie == 0)
      {                           // variabele wordt ingevoerd zodat studie en diens tijd niet flikkert
        lcd.setCursor(11, 1);     // juiste plaats zetten waar 'pauze' verwijderd moet worden
        lcd.print("           "); // 'pauze' verwijderen
        studie++;
      }
      lcd.setCursor(5, 1);
      lcd.print(" stud:");
      hoeveelPauze = minuten * 2 + seconden / 30; // eerst de hoeveelheid definiëren dat de gebruiker pauze heeft
      if (hoeveelPauze > 4)
      { // na 4 keer pauze volgt een lange pauze, berekenen hoeveel deze voorkomt
        langePauze = hoeveelPauze / 5;
      }
      hoeveelPauze = (hoeveelPauze + langePauze) * 5;
      langePauze = 0;                                // terug resetten, anders blijft tijd bijkomen
      int totaalStudieSec = minuten * 60 + seconden; // gehele tijd omzetten naar seconden
      int totaalPauzeSec = hoeveelPauze;

      int resultaatSec = totaalStudieSec - totaalPauzeSec; // hoeveel seconden effectieve studietijd

      hoeveelStudieMin = resultaatSec / 60; // terug naar min + sec
      hoeveelStudieSec = resultaatSec % 60;

      if (hoeveelStudieMin < 10)
      {
        lcd.print("0"); // voor mooie tijden
      }
      if (hoeveelStudieMin < 0)
      {
        hoeveelStudieMin = 0; // voor mooie tijden
      }
      lcd.print(hoeveelStudieMin); // uitprinten
      lcd.print(":");
      if (hoeveelStudieSec < 10)
      {
        lcd.print("0"); // voor mooie tijden
      }
      if (hoeveelStudieSec < 10)
      {
        lcd.print("0"); // voor mooie tijden
      }

      lcd.print(hoeveelStudieSec);
    }
    break;
  }
  // speaker toevoegen: speaker laten werken wanneer de status van de Leds verandert
  if (ledState != vorigeState)
  {
    tone(speaker, 262, 100);
    vorigeState = ledState;
  }
}
```