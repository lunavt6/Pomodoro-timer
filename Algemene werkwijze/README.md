# Algemene werkwijze

De opbouw van de finale code van de code ging als volgt:
1. De code voor de verschillende componenten werd eerst apart geschreven, zo kon van elk component de werking getest worden aan de hand van WokWi-simulaties en konden nodige functies geïdentificeerd worden, die componentafhankelijk waren. Hierbij werd gebruik gemaakt van librarys en wat in de lessen werd aangeleerd.
    - [code buzzer](<Arduino/Aparte onderdelen/deel_geluid.ino>)
    In deze code was het doel om de buzzer geluid te laten maken, dit werd gedaan met de functie 'tone'.
    - [code knoppen](<Arduino/Aparte onderdelen/deel_knoppen.ino>)
    In deze code werd de code geschreven voor 2 knoppen. Deze zorgen voor het instellen van de tijd: +/- 30 seconden. Dit werd apart gemaakt aangezien dit een aparte functie was, die enkel bij de knoppen hoorden en geen andere componenten. De aan/uit knop en de knop om te beginnen aftellen moeten toegevoegd worden bij het samenbrengen van de verschillende componenten.
    - [code LED-lichten](<Arduino/Aparte onderdelen/deel_leds.ino>)
    In deze code worden 2 ledlichten afwisselend aan en uit geschakeld, bij elke verandering wordt vervolgens een boodschap geprint. Het doel van deze code is dus om de ledstaten de veranderen na aangegeven tijdsspannes, dit is ook nodig in de finale code.
    - [code scherm](<Arduino/Aparte onderdelen/deel_scherm.ino>)
    In deze code werd voornamelijk onderzocht hoe het LCD-scherm diende aangestuurd te worden en welke libraries hiervoor vereist werden. Het scherm print hier enkel een boodschap.




2. De code van de LED's en de buzzer werd vervolgens samengevoegd, alsook degene van het scherm en de knoppen.
    - [code LED + buzzer](<../Arduino/Gelinkte onderdelen/deel_geluid_en_LED.ino>)
    In deze code werden de LED's gekoppeld aan de buzzer, bij elke statusverandering zal nu een geluid klinken.
    - [code knoppen+scherm](<../Arduino/Gelinkte onderdelen/deel_scherm_en_knoppen.ino>)
    In deze code worden de laatste 2 knoppen bijgevoegd: aan/uit en het lopen van de timer. Verder wordt ervoor gezorgd dat alle knoppen interageren met het scherm zonder dat dit knippert.




3. Finaal werden beide codes samengevoegd tot een geheel werkend product.
    - [code finaal](../Arduino/samenstelling_onderdelen/samenstelling_onderdelen.ino)
    In deze code worden alle componenten samengevoegd. De LED's zullen uitzonderlijk branden wanneer de timer loopt. Bij elke indrukking van een knop maakt de buzzer geluid en de boodschappen die op het scherm verschijnen zijn verbonden met de statusveranderingen van de LED's.
    Verder wordt een effectieve studietijd toegevoegd, dit is de tijd die effectief gestudeerd zal worden.