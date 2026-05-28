int knop1 = 6; // knop voor scherm aan/uit
int knop2 = 8; // knop voor + tijd
int knop3 = 10; // knop voor - tijd
int knop4 = 13; // knop voor start timer

void setup()
{
  Serial.begin(9600);

  pinMode(knop1, INPUT_PULLUP);
  pinMode(knop2, INPUT_PULLUP);
  pinMode(knop3, INPUT_PULLUP);
  pinMode(knop4, INPUT_PULLUP);
}

void loop()
{
  // Knoppen lang indrukken om beste resultaat te krijgen

  // Test aan en uit knop
  if (digitalRead(knop1) == LOW)
  {
    Serial.println("Knop 1 (pin 6): INGEDRUKT");
  }
  else
  {
    Serial.println("Knop 1 (pin 6): LOS");
  }

  // Test + tijd knop
  if (digitalRead(knop2) == LOW)
  {
    Serial.println("Knop 2 (pin 8): INGEDRUKT");
  }
  else
  {
    Serial.println("Knop 2 (pin 8): LOS");
  }

  // Test - tijd knop
  if (digitalRead(knop3) == LOW)
  {
    Serial.println("Knop 3 (pin 10): INGEDRUKT");
  }
  else
  {
    Serial.println("Knop 3 (pin 10): LOS");
  }

  // Test start timer knop
  if (digitalRead(knop4) == LOW)
  {
    Serial.println("Knop 4 (pin 13): INGEDRUKT");
  }
  else
  {
    Serial.println("Knop 4 (pin 13): LOS");
  }

  Serial.println("Klaar!");
  Serial.println();

  delay(1000);
}
