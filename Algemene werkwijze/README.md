# Algemene werkwijze

De opbouw van de finale code van de code ging als volgt:<br>
1. De code voor de verschillende componenten werd eerst apart geschreven. Zo kon van elk component de werking getest worden via WokWi-simulaties en konden noodzakelijke functies geïdentificeerd worden. Hierbij werd gebruikgemaakt van libraries en de leerstof uit de lessen.<br>

    - Buzzer:
    De buzzer werd getest met de functie `tone()` om geluid te genereren.<br>
    <a href="https://wokwi.com/projects/460822150091629569">
      <img src="opstelling_geluid.png" width="300">
    </a><br><br>

    - Knoppen:
    Deze code bevat de werking van 2 knoppen. Die zorgen voor het instellen van de tijd: +/- 30 seconden. De aan/uit knop en de knop om het agtellen te beginnen moeten later toegevoegd worden bij het samenbrengen van de verschillende componenten.<br>
    <a href="https://wokwi.com/projects/461272536199758849 ">
      <img src="deel knoppen apart.png" width="300">
    </a><br><br>

    - LED's:
    In deze code werden 2 ledlichten afwisselend aan- en uitgeschakeld, bij elke verandering werd vervolgens een boodschap geprint. Het doel van deze code is om de staat van de LED's de veranderen na aangegeven tijdsspannes.<br><br>
    <a href="https://wokwi.com/projects/461272267489519617">
      <img src="opstelling_leds.png" width="300">
    </a><br><br>

    - Scherm:
    In deze code werd voornamelijk onderzocht hoe het LCD-scherm diende aangestuurd te worden en welke libraries hiervoor vereist waren. Het scherm printte hierbij enkel een boodschap.<br>
    <a href="https://wokwi.com/projects/462175882081870849">
      <img src="deel scherm.png" width="300">
    </a><br><br>

<br>


2. De codes van de LED's en de buzzer werden vervolgens samengevoegd, alsook degene van het scherm en de knoppen.<br>

    - Buzzer + LED's:
    In deze code werden de LED's gekoppeld aan de buzzer, bij elke statusverandering zal nu een geluid klinken.<br>
    <a href="https://wokwi.com/projects/462172590186935297">
      <img src="deel LED+buzzer Wokwi.png" width="300">
    </a><br><br>

    - Knoppen + scherm:
    In deze code werden de laatste 2 knoppen bijgevoegd: aan/uit en het starten van de timer. 
    Verder werd ervoor gezorgd dat alle knoppen interageren met het scherm zonder dat dit knippert.<br>
    <a href="https://wokwi.com/projects/463446687865780225">
      <img src="deel knoppen+scherm.png" width="300">
    </a><br><br>

<br>


3. Finaal werden beide codes samengevoegd tot een geheel werkend product.<br>
    - Finale samenstelling:
    In deze code werden alle componenten samengevoegd. De LED's zullen uitzonderlijk branden wanneer de timer loopt. 
    Bij elke LED-verandering, het indrukken van de aan/uit-knop en bij het starten van de timer klinkt een geluid.
    De boodschappen die op het scherm verschijnen, zijn verbonden met de statusveranderingen van de LED's.
    Verder werd een effectieve studietijd toegevoegd, dit is de tijd zonder pauze.
    Het scherm werd aangesloten op een component die slechts 4 pinnen vereist, dit zorgt voor extra gebruiksgemak bij het aansluiten van de pinnen.<br>
    <a href="https://wokwi.com/projects/462923072193805313">
      <img src="opstelling_alle_componenten.png" width="300">
    </a><br><br>

>De codes van al deze afzonderlijeke stappen kunnen [hier](../Arduino/README.md) terug gevonden worden.

>OPMERKING: De afbeeldingen bevatten een link naar de WokWi-simulatie. De aparte links kunnen [hier](../Docs/links.md)terug gevonden worden.