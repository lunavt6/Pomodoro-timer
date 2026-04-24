// include the library code:
#include <LiquidCrystal.h>
int WaardeKnop;
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, e = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, e, d4, d5, d6, d7);
int AanUit=7;
int Toestand;
int VorigeKnop;
// knop
int knop = 6;
unsigned long laatsteDruk;

void setup() {
  // set up the LCD's number of columns and rows:
  pinMode(knop, INPUT_PULLUP);
  pinMode(AanUit, OUTPUT);
  digitalWrite(7, LOW);
  Toestand=0;
  lcd.begin(16, 2);
  VorigeKnop=HIGH;
}

void loop() {
  WaardeKnop = digitalRead(knop);

if (WaardeKnop == LOW && VorigeKnop == HIGH) {

  if (millis() - laatsteDruk > 200) {

    Toestand = !Toestand;
    laatsteDruk = millis();

    if (Toestand == 1) {
      digitalWrite(AanUit, HIGH);
      lcd.display();
      lcd.clear();
      lcd.print("Tijd instellen");
    } else {
      digitalWrite(AanUit, LOW);
      lcd.noDisplay();
    }
  }
}

VorigeKnop = WaardeKnop; 
}
