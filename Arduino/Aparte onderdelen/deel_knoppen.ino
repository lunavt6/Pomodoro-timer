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