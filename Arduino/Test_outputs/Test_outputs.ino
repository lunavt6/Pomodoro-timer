// bibliotheek initialiseren nodig voor het LED-scherm
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Stel het aantal kolommen en rijen van het LCD-scherm in:
LiquidCrystal_I2C lcd(0x27, 16, 2);


int ledPinG = A0;
int ledPinR = A1;
int speaker = 9;

void setup()
{
  Serial.begin(9600);

  pinMode(ledPinG, OUTPUT);
  pinMode(ledPinR, OUTPUT);
  pinMode(speaker, OUTPUT);
}

void loop()
{

  // LCD backlight test 
  // backlight aanleggen
  Serial.println("Backlight AAN");
  lcd.backlight();
  delay(1500);

  //backlight uitleggen
  Serial.println("Backlight UIT");
  lcd.noBacklight();
  delay(1500);

  // Groene LED test 
  // Groene LED aanleggen
  Serial.println("Groene LED AAN");
  digitalWrite(ledPinG, HIGH);
  delay(1500);

  // Groene LED uitleggen
  Serial.println("Groene LED UIT");
  digitalWrite(ledPinG, LOW);
  delay(1500);

  // Rode LED test 
  // Rode LED aanleggen
  Serial.println("Rode LED AAN");
  digitalWrite(ledPinR, HIGH);
  delay(1500);

  // Rode LED uitleggen
  Serial.println("Rode LED UIT");
  digitalWrite(ledPinR, LOW);
  delay(1500);

  // Speaker test
  Serial.println("Speaker test (toon)");
  tone(speaker, 262); // speaker aanleggen
  delay(500);
  noTone(speaker); // speaker uitleggen

  delay(1000);

  Serial.println("Klaar!");
  Serial.println(" "); // leeg lijntje toevoegen
}