// initialize the library by associating any needed LCD interface pin
#include <LiquidCrystal.h>

 // Stel het aantal kolommen en rijen van het LCD-scherm in:
const int rs = 12, e = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, e, d4, d5, d6, d7);
int AanUit=7; // voor 'A', om backlight aan en uit te zetten
int Toestand;

//variabelen nodig voor knoppen
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
int VorigeKnop3 ;
int waarde = 0;
int minuten = 00;
int seconden = 00;

int WaardeKnop4;
int VorigeKnop4;
int i;
int j;

// variabelen nodig voor timer
bool timerLoopt=false;
unsigned long laatstetijd=0;

//variabelen voor debounce, vloeiende werking
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay =50;
unsigned long lastDebounceTime4;

//variabelen nodig voor speaker
int speaker = 9;

// variabelen nodig voor Led's
int ledPinR = A1;
int ledPinG =A0;
unsigned long vorigeTijd;


enum LedStates {
  LED_UIT_G_LED_UIT_R,
  LED_AAN_G_LED_UIT_R,
  LED_UIT_G_LED_AAN_R
};
LedStates vorigeState = LED_UIT_G_LED_UIT_R;
LedStates ledState = LED_UIT_G_LED_UIT_R; // toestel staat uit

//variabelen nodig voor pauze
int teller=0;
int pauze=false;

void setup() {
//PinModes output of input instellen
  pinMode(knop1, INPUT_PULLUP);
  pinMode(knop2, INPUT_PULLUP);
  pinMode(knop3, INPUT_PULLUP);
  pinMode(knop4, INPUT_PULLUP);
  pinMode(AanUit, OUTPUT);
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinG, OUTPUT);
  pinMode(speaker, OUTPUT);
  digitalWrite(7, LOW);
//Initiële waarden goedzetten
  Toestand=0;
  VorigeKnop1=HIGH;
  VorigeKnop2=HIGH;
  VorigeKnop3=HIGH;
  VorigeKnop4=HIGH;
   lcd.begin(16, 2);
  Serial.begin(9600);
  vorigeTijd = millis();
  digitalWrite(ledPinG, LOW);
  digitalWrite(ledPinR, LOW);
}

void loop() {
  //knop 1: aan/uit LCD-scherm code

WaardeKnop1 = digitalRead(knop1);

if (WaardeKnop1 == LOW and VorigeKnop1 == HIGH) { //nieuwe indrukking

  if (millis() - laatsteDruk1 > 200) { //debounce code

    Toestand = !Toestand; // om aan te duiden of scherm aan of uit moet
    laatsteDruk1 = millis();

    if (Toestand == 1) {
      digitalWrite(AanUit, HIGH); // backlight aanzetten
      lcd.display(); // tekst aanzetten
      lcd.clear(); // zorgen dat er geen tekst staat
      lcd.print("Tijd instellen");
    } 
    else {
      digitalWrite(AanUit, LOW); //backlight afzetten
      lcd.noDisplay(); //display uizetten
    }
  }
}
VorigeKnop1 = WaardeKnop1; // zodat de toestand niet constant verandert bij het binnenhalen van signalen

// knop 2 en 3: tijd verhogen en verlagen

  int reading_H = digitalRead(knop2);
  int reading_L = digitalRead(knop3);

  if (reading_H != VorigeKnop2) { // knop 2 verandert van staat, ontvangt signaalverandering, pas als bounce lang genoeg gestopt 1 en die 1 signaal ontvangt wordt verder gegaan
    lastDebounceTime = millis(); 
  }

  if (reading_L != VorigeKnop3){ // knop 3 verandert van staat
    lastDebounceTime= millis();
  }
// voor knop 2: optellen
  if ((millis()-lastDebounceTime)>debounceDelay) { // debounce, het lukt om status te veranderen, vertraging introduceren zodat bij eenmaal contact de status verandert
    if (reading_H != WaardeKnop2){ 
      WaardeKnop2 = reading_H; // wordt geregistreerd zonder de bouce, anders zou volgende if meerder keren doorlopen worden
      if (WaardeKnop2 == LOW){
        waarde++;// begint bij waarde 0, aan de hand van even of oneven zullen de minuten bepaald worden
        if (waarde%2==0){ // waarde is even, bv. Waarde=2, is er 2 keer 30 seconden opgetelt dus 1 min
          minuten= waarde/2;
          seconden =0;
          }
        if (waarde%2==1){ // waarde is oneven, bv 1, dus 1 keer 30 seconden
          minuten = waarde/2;
          seconden =30;
          }
  
      }
    }
  }
// voor knop 3: aftrekken (zelfde als voorheen)
  if ((millis()-lastDebounceTime)>debounceDelay) {
    if (reading_L != WaardeKnop3){
      WaardeKnop3 = reading_L;
      if (WaardeKnop3 == LOW){
        waarde--;
        if (waarde%2==0){
          minuten= waarde/2;
          seconden =0;
          }
        if (waarde%2==1){
          minuten = waarde/2;
          seconden =30;
          }
      }
    }
  }
  VorigeKnop2 = reading_H; // om signaalverandering van signaal op te vangen
  VorigeKnop3 = reading_L;

//knop 4: tijd start met lopen

  VorigeKnop2 = reading_H;
  VorigeKnop3 = reading_L;

  WaardeKnop4 = digitalRead(knop4);

if (WaardeKnop4 == LOW and VorigeKnop4 == HIGH) {
  if (millis() - lastDebounceTime4 > debounceDelay) { // zelfde als voorheen: debounce
    timerLoopt = !timerLoopt; // verandering in of timer moet aflopen of stoppen met aflopen wanneer knop ingeduwd wordt
    lastDebounceTime4 = millis(); // laatste indrukking knop

    if (timerLoopt) {// als de timer loop zijn de beginwaarden..
      i = minuten;
      j = seconden;
      laatstetijd = millis();
    }
  }
}
VorigeKnop4 = WaardeKnop4; // na doorlopen vorige code mag waarde aangepast worden

// aftellende timer

  if (timerLoopt) {
    if (millis() - laatstetijd >= 1000) { // nadat 1 seconde verlopen is mag de seconde-waarde aangepast worden
    laatstetijd = millis();
    j--;

    if (j < 0) { // als j negatief wordt verminderen de min, en start een nieuwe minuut
      j = 59;
      i--;
    }

    if (i < 0) { // als i vervolgens negatief wordt, stopt de timer
      i = 0;
      j = 0;
      timerLoopt = false;
      teller++; // zal pauzeduur bepalen, na het stoppen van de timer is er een cyclus doorlopen
      pauze=true; // zal verderop ervoor zorgen dat het systeem gedurende een tijd niets meer doet, deze variabele zorgt ervoor dat het systeem voor de eerste cyclus ook werkt
      tone(speaker, 262, 100); // wanneer de timer gedaan is weerklinkt een geluid om de gebruiker te alarmeren
    }
  }
}
// de tijd op het scherm printen

lcd.setCursor(0, 1); // juiste plaats zetten waar tekst geprint zal worden

if (digitalRead(AanUit) == HIGH) { // het backlight moet aanstaan, er moet dus op de aan/uit knop geduwd zijn om iets te printen op het scherm

  if (timerLoopt) { // als de timer loopt , wordt gewoon telkens de geüpdate tijd geprint
    lcd.print(i);
    lcd.print(":");
    if (j < 10) lcd.print("0"); // ervoor zorgen dat de minuten telkens met 2 cijfers worden weergegeven
    lcd.print(j); 
  } else { // als de timer niet loopt, moeten gewoon de ingegeven waarden door knop2 en 3 weergegeven worden
    lcd.print(minuten);
    lcd.print(":");
    if (seconden < 10) lcd.print("0");
    lcd.print(seconden);
  }

} else { // als het scherm niet aanstaat mag er ook geen tekst weergegeven worden
  lcd.clear(); 
}

//Led's toevoegen

if(digitalRead(AanUit)==LOW){ // als het scherm niet aanstaat, mogen de led's ook nog niet branden
    ledState=LED_UIT_G_LED_UIT_R;
  }
else if (timerLoopt){ // als de timer loopt en het scherm staat aan, dan is de groene led aan
    ledState=LED_AAN_G_LED_UIT_R;
  }
else { // als het scherm aanstaat en de timer niet loopt, brandt de rode Led
    ledState=LED_UIT_G_LED_AAN_R;
  }
  // Leds laten branden, bij variabelen de juiste led's laten branden

if (ledState == LED_AAN_G_LED_UIT_R){ //toestel uit -> studeertijd
  
  digitalWrite(ledPinG, HIGH);
  digitalWrite(ledPinR, LOW);
    }
else if (ledState == LED_UIT_G_LED_AAN_R) { // studeertijd -> pauze
  
  digitalWrite(ledPinG, LOW);
  digitalWrite(ledPinR, HIGH);
  // als rood aan is kan er pauze zijn, om dit te controleren werd de variabele pauze eerder geïntroduceerd
  if (teller<5 and pauze==true){  // na 5 cycli vindt een langere pauze plaats
    delay(5000);
    tone(speaker, 262, 100); // na de pauze klinkt een toon om de gebruiker te alarmeren dat de pauze geaan is
    pauze=false; // de variabele wordt terug goed gezet opdat de cyclus niet opnieuw doorlopen zal worden en de tijd opnieuw ingesteld kan worden
  }
  if (teller==5 and pauze == true){
    delay(10000); // een langere pauze
    teller=0; // na 5 cycli wordt dan opnieuw een lange pauze gegeven
    tone(speaker, 262, 100);
    pauze=false; // idem als voorheen
  }
    }
else{ // pauze -> uit
  
  digitalWrite(ledPinG, LOW);
  digitalWrite(ledPinR, LOW);
    }
  //speaker toevoegen: speaker laten werken wanneer de status van de Leds veandert
  if (ledState != vorigeState) {
  tone(speaker, 262, 100);
  vorigeState = ledState;
}
}

