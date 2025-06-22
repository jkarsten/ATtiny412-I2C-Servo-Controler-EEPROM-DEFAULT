#📝 EEPROM Defaultwert-Writer für ATtiny412

- Fügt ein separates Sketch zum Schreiben von Standardwerten in den EEPROM hinzu
- Werte:
  - Startposition: 90
  - Anfang: 0
  - Ende: 180
  - Speed: 0
  - I²C-Adresse: 0x08
  - PulseMin: 500 µs
  - PulseMax: 2500 µs
- Schreibt zusätzlich eine XOR-Checksumme zur Validierung der Daten (Adresse 0x09)
- Nach dem Schreiben:
  - EEPROM wird erneut gelesen
  - Checksumme wird neu berechnet
  - LED zeigt Status:
    - Dauerlicht → Werte korrekt geschrieben
    - Blinken → Schreib-/Lesefehler erkannt
