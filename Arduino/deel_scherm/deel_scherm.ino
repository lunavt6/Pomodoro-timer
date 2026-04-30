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