# Simulateur ErgonomicWorkstation 2024

## Présentation du protocole implanté dans le simulateur ESP'ACE

Ce document présente rapidement le fonctionnement du simulateur ainsi que le protocole implémenté.

> Le protocole complet est disponible dans Google Drive.

## platform.ini

```ini
[env:lolin32]
platform = espressif32
board = lolin32
framework = arduino
lib_deps =
  thingpulse/ESP8266 and ESP32 OLED driver for SSD1306 displays @ ^4.2.0
upload_port = /dev/ttyUSB0
upload_speed = 115200
monitor_port = /dev/ttyUSB0
monitor_speed = 115200
```

## Protocole

- Trame ASCII
- Délimiteur de début : `$`
- Délimiteur de fin : `\n`
- Séparateur de champs : `;`

### Trame envoyée par le poste de travail

Format : `$[TYPE];[DONNEE]\n`

- Type de trame : ‘`E`’ (encodeur)
- Donnée : 

- ‘`1`’ pour droite
- ‘`2`’ pour gauche
- ‘`3`’ pour validation

Exemples :

- `$E;2\n` : l'encodeur a été” déplacé d’un “cran” vers la gauche
- `$E;3\n` : appui sur l’encodeur

## Auteur

- Thierry Vaira <<tvaira@free.fr>>
