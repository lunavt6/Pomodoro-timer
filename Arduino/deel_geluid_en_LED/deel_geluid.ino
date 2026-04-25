int speaker = 4;


void setup() {
  // put your setup code here, to run once:
  pinMode(speaker, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  tone(speaker, 262, 100); // frequentie = 262, tijd = 0.1 s
  delay(5000); // 5 seconden tussen elke beep
  //noTone(speaker); -> geen idee wat dit doet, hoor geen verschil met of zonder
}


