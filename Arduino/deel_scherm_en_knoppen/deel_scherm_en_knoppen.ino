#include <LiquidCrystal.h>
int WaardeKnop1;
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, e = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, e, d4, d5, d6, d7);
int AanUit=7;
int Toestand;
int VorigeKnop1;
// knop
int knop1 = 6;
int knop2 = 8;
int knop3 = 10;
int knop4 = 13;

unsigned long laatsteDruk1;

int WaardeKnop2; 
int VorigeKnop2;
int WaardeKnop3;
int VorigeKnop3 ;
int waarde = 0;
int uur = 00;
int minuten = 00;


unsigned long lastDebounceTime = 0;
unsigned long debounceDelay =50;

void setup() {
  // set up the LCD's number of columns and rows:
  pinMode(knop1, INPUT_PULLUP);
  pinMode(knop2, INPUT_PULLUP);
  pinMode(knop3, INPUT_PULLUP);
  pinMode(knop4, INPUT_PULLUP);
  pinMode(AanUit, OUTPUT);
  digitalWrite(7, LOW);
  Toestand=0;
  lcd.begin(16, 2);
  VorigeKnop1=HIGH;
  VorigeKnop2=HIGH;
  VorigeKnop3=HIGH;
  Serial.begin(9600);
}

void loop() {
  WaardeKnop1 = digitalRead(knop1);

if (WaardeKnop1 == LOW and VorigeKnop1 == HIGH) {

  if (millis() - laatsteDruk1 > 200) {

    Toestand = !Toestand;
    laatsteDruk1 = millis();

    if (Toestand == 1) {
      digitalWrite(AanUit, HIGH);
      lcd.display();
      lcd.clear();
      lcd.print("Tijd instellen");
    } else {
      digitalWrite(AanUit, LOW);
      lcd.clear();
    }
  }
}
VorigeKnop1 = WaardeKnop1; 

  // put your main code here, to run repeatedly:
  int reading_H = digitalRead(knop2);
  int reading_L = digitalRead(knop3);

  if (reading_H != VorigeKnop2) {
    lastDebounceTime = millis();
  }

  if (reading_L != VorigeKnop3){
    lastDebounceTime= millis();
  }

  if ((millis()-lastDebounceTime)>debounceDelay) {
    if (reading_H != WaardeKnop2){
      WaardeKnop2 = reading_H;
      if (WaardeKnop2 == LOW){
        waarde++;
        if (waarde%2==0){
          uur= waarde/2;
          minuten =0;
          }
        if (waarde%2==1){
          uur = waarde/2;
          minuten =30;
          }
  
      }
    }
  }

  if ((millis()-lastDebounceTime)>debounceDelay) {
    if (reading_L != WaardeKnop3){
      WaardeKnop3 = reading_L;
      if (WaardeKnop3 == LOW){
        waarde--;
        if (waarde%2==0){
          uur= waarde/2;
          minuten =0;
          }
        if (waarde%2==1){
          uur = waarde/2;
          minuten =30;
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



  VorigeKnop2 = reading_H;
  VorigeKnop3 = reading_L;
  
}
