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
      Serial.println("Nieuwe state: " ledState);
    }
    else if (ledState == LED_AAN_G_LED_UIT_R) { // studeertijd -> pauze
      tone(speaker, 262, 100);
      ledState = LED_UIT_G_LED_AAN_R;
      digitalWrite(ledPinG, LOW);
      digitalWrite(ledPinR, HIGH);
      Serial.println("Nieuwe state: " ledState);
    }
    else // pauze -> uit
      tone(speaker, 262, 100);
      ledState = LED_UIT_G_LED_UIT_R;
      digitalWrite(ledPinG, LOW);
      digitalWrite(ledPinR, LOW);
      Serial.println("Nieuwe state: " ledState);
    }

  }
