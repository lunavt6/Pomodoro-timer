# Pomodoro-timer

## Teamleden
- Leen Geenens
- Loes Vanmeerbeek
- Luna Van Tittelboom

## Doelstellingen
1. Vooraf instellen hoelang er gestudeerd moet worden.
    - Het instellen gebeurt in sprongen van 30 minuten.
    - Pauze zit er dus ingerekend.
2. Na elke 25 minuten werken volgt er een pauze van 5 minuten pauze.
3. Na vier keer stap 2 te doorlopen volgt er een pauze van 30 minuten.

In arduino:
- werken = 25 seconden
- korte pauze = 5 seconden
- lange pauze = 10 seconden + 5 seconden 

## Verschillende componenten

### Scherm
Hierop zie je de tijd en kan je instellen hoe lang je wilt werken. Naast het instellen wordt er ook weergegeven hoeveel tijd je werkelijk studeert, dus de tijd zonder pauzes. 

<img src="Imgs/scherm_opstart.png" width="300">

Het scherm zal ook weergeven in welke status je je bevindt, zo verschijnt er studeren op wanneer het groene lichtje brandt en (lange) pauze wanneer het rode lichtje brandt.

<img src="Imgs/scherm_studeren.png" width="300">
<img src="Imgs/scherm_pauze.png" width="300">
<img src="Imgs/scherm_lange_pauze.png" width="300">



### Knoppen
De timer zal in totaal vier verschillende knoppen hebben:
- Een aan- en uitknop
- Een knop om de timer te starten
- Een knop om de tijd te verhogen
- Een knop om de tijd te verlagen

![alt text](Imgs/aanuit.png)![alt text](Imgs/start.png)![alt text](Imgs/plus.png)![alt text](Imgs/min.png)

### Leds
Er zullen twee leds aanwezig zijn.
- Een groen ledje voor tijdens het studeren.
- Een rood ledje voor tijdens de pauze.

Deze leds branden wanneer er op de knop om de timer te starten wordt gedrukt.

![rode led](<Imgs/rode led.png>)![groene led](<Imgs/groene led.png>)

### Geluid
Bij elke kleurwisseling van de leds zal er een ping geluid te horen zijn, alsook bij het starten en eindigen van de timer.

## Algemene werking

Onderstaand is een schema weergegeven waarin functies en componenten verbonden staan om te illustreren wat met elkaar verbonden is.

![schema algemene werking](<Imgs/schema algemene werking.png>)


## Algemene werkwijze
De opbouw van de code ging als volgt:
- De code voor de componenten werd apart geschreven, zo kon van elk de werking getest worden.
- De code van de leds en de speaker werd vervolgens samengevoegd, alsook degene van het scherm en de knoppen.
- Finaal werden beide codes samengevoegd tot een geheel werkend product.

## Documenten
1. [Links](Docs/links.md)
2. [Opstellingen](Docs/opstellingen.md)
3. [videos](<Filmpjes fysieke opstellingen/README.md>)

## kritische reflectie

Tijdens dit project hebben we veel nieuwe kennis en vaardigheden opgedaan, aangezien dit onze eerste ervaring was met Arduino. Tijdens het proces kwamen we verschillende uitdagingen tegen die ons hielpen om beter inzicht te krijgen in zowel hardware als software.

Een moeilijkheid was het probleem van de knopdebounce. In het begin zorgde dit voor onstabiele invoer, maar na verder onderzoek en testen slaagden we erin om hiervoor een individueel een oplossing implementeerde, waardoor dit nu in de code op verschillende manieren word opgelost.

Daarnaast bleek ook de fysieke aansluiting van het scherm complexer dan verwacht. Om dit probleem te vereenvoudigen, hebben we uiteindelijk gebruikgemaakt van een component die de verbinding van het scherm reduceerde tot slechts vier pinnen, wat de integratie aanzienlijk vergemakkelijkte.

Het project werd echter als een moeilijk proces ervaren, omdat we voortdurend verschillende technische problemen moesten oplossen. Zo moesten we ervoor zorgen dat de tijd correct bleef aftellen, dat het scherm niet begon te knipperen en dat tekst niet over elkaar heen werd geschreven. Daarnaast liep de tijd aanvankelijk niet verder door tijdens de lange pauze, wat eveneens opgelost moest worden. Ook bij het opnieuw opstarten van het systeem mochten oude teksten niet overschreven worden en moest het volledige scherm correct leeggemaakt worden bij het uitschakelen zodat alle tekst verdween. Deze problemen vereisten veel testen, aanpassen en opnieuw programmeren.

Doorheen het project hebben we meerdere iteraties doorlopen waarbij we stap voor stap componenten samenbrachten, nieuwe functionaliteiten toevoegden en problemen oplosten die tijdens het proces naar voren kwamen. Achteraf bekeken hadden we onze code compacter en overzichtelijker kunnen maken door vaker gebruik te maken van functies en een betere structuur in de code aan te brengen.

