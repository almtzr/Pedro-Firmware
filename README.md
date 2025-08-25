# Pedro-Firmware

## Description
[Pedro](https://pedrobot.com) est un robot éducatif open-source. Ce dépôt contient le code source du firmware pour la carte Pedro.

## Installation de la bibliothèque Arduino
1. Téléchargez le fichier `Pedro.zip` du dossier `libraries/`.
2. Ouvrez l'IDE Arduino.
3. Allez dans `Croquis > Inclure une bibliothèque > Ajouter la bibliothèque .ZIP`.
4. Sélectionnez le fichier `Pedro.zip`.

## Compilation et Flashage du Firmware
1. Ouvrez le fichier `pedro_main.ino` dans l'IDE Arduino.
2. Sélectionnez la bonne carte (Arduino Uno ou autre).
3. Cliquez sur **Téléverser** pour compiler et flasher le firmware.

## Flashage avec avrdude
Vous pouvez également flasher le firmware directement via `avrdude` ou l'application IHM Python :
```bash
avrdude -v -p m328p -c arduino -P /dev/ttyUSB0 -b 115200 -D -U flash:w:pedro_main.hex:i
