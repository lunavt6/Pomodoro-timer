# Algemene werkwijze

De opbouw van de finale code van de code ging als volgt:<br>
1. De code voor de verschillende componenten werd eerst apart geschreven. Zo kon van elk component de werking getest worden via WokWi-simulaties en konden noodzakelijke functies geïdentificeerd worden. Hierbij werd gebruikgemaakt van libraries en de leerstof uit de lessen.

    - Buzzer
    De buzzer werd getest met de functie `tone()` om geluid te genereren.
    - Knoppen
    Deze code bevat de werking van 2 knoppen, deze zorgen voor het instellen van de tijd: +/- 30 seconden. De aan/uit knop en de knop om te beginnen aftellen moeten toegevoegd worden bij het samenbrengen van de verschillende componenten.
    - LED's
    In deze code worden 2 ledlichten afwisselend aan en uit geschakeld, bij elke verandering wordt vervolgens een boodschap geprint. Het doel van deze code is om de ledstaten de veranderen na aangegeven tijdsspannes.
    - Scherm
    In deze code werd voornamelijk onderzocht hoe het LCD-scherm diende aangestuurd te worden en welke libraries hiervoor vereist werden. Het scherm printte hierbij enkel een boodschap.

<br>


2. De code van de LED's en de buzzer werd vervolgens samengevoegd, alsook degene van het scherm en de knoppen.<br>
    - Buzzer + LED's
    In deze code werden de LED's gekoppeld aan de buzzer, bij elke statusverandering zal nu een geluid klinken.
    - Knoppen + scherm
    In deze code worden de laatste 2 knoppen bijgevoegd: aan/uit en het starten van de timer. 
    Verder wordt ervoor gezorgd dat alle knoppen interageren met het scherm zonder dat dit knippert.

<br>


3. Finaal werden beide codes samengevoegd tot een geheel werkend product.<br>
    - Finale samenstelling
    In deze code worden alle componenten samengevoegd. De LED's zullen uitzonderlijk branden wanneer de timer loopt. 
    Bij elke LED-verandering, het indrukken van de aan/uit-knop en bij het startenvan de timer klinkt een geluid.
    De boodschappen die op het scherm verschijnen zijn verbonden met de statusveranderingen van de LED's.
    Verder wordt een effectieve studietijd toegevoegd, dit is de tijd die effectief gestudeerd zal worden.


>De codes zijn [hier](../Arduino/README.md) terug te vinden.