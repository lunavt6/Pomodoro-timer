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
}

void loop() {
  
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
