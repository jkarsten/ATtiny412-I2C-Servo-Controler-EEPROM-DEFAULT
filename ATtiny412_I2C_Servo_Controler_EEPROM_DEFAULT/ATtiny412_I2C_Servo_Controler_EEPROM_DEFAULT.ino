// =====================================
//  ATtiny412 - I²C Servo Controler - Default Werte
// =====================================
// Kurzes Sketch um Standardwerte in ATtiny 412 zu schreiben
//
// BOD Mode when Active /Sleeping:  "Enabled/Enabled"
// BOD Voltage Level:               "4.2V (20 MHZ or less)"
// Chip:                            "ATtiny412"
// Clock:                           "20 MHz internal"
// PWN pins:                        "PA1-3, 7 (default)"
// Save EEPROM:                     "EEPROM retained"

#include <avr/io.h>
#include <avr/eeprom.h>

// =====================================
// Konfiguration & EEPROM-Zuordnung
// =====================================
#define DEFAULT_START_POSITION 90
#define DEFAULT_ANFANG 0
#define DEFAULT_ENDE 180
#define DEFAULT_SPEED 0
#define DEFAULT_I2C_ADRESSE 0x08
#define DEFAULT_PULSE_MIN 500
#define DEFAULT_PULSE_MAX 2500

#define EEPROM_ADDR_START_POSITION 0x00
#define EEPROM_ADDR_ANFANG 0x01
#define EEPROM_ADDR_ENDE 0x02
#define EEPROM_ADDR_SPEED 0x03
#define EEPROM_ADDR_I2C_ADRESSE 0x04
#define EEPROM_ADDR_PULSE_MIN 0x05  // Word: 0x05 + 0x06
#define EEPROM_ADDR_PULSE_MAX 0x07  // Word: 0x07 + 0x08
#define EEPROM_ADDR_CHECKSUM 0x09

void setup() {
  VPORTA.DIR |= PIN3_bm;  // LED PIN als Ausgang

  // ==============================================
  // Werte in EEPROM Speicher
  // ==============================================

  // Schreibe die Standardwerte in den EEPROM mit kleinen Pausen
  eeprom_write_byte((uint8_t*)EEPROM_ADDR_START_POSITION, DEFAULT_START_POSITION);  // ServoStartPosition
  delay(5);
  eeprom_write_byte((uint8_t*)EEPROM_ADDR_ANFANG, DEFAULT_ANFANG);  // ServoAnfang
  delay(5);
  eeprom_write_byte((uint8_t*)EEPROM_ADDR_ENDE, DEFAULT_ENDE);  // ServoEnde
  delay(5);
  eeprom_write_byte((uint8_t*)EEPROM_ADDR_SPEED, DEFAULT_SPEED);  // ServoSpeed
  delay(5);
  eeprom_write_byte((uint8_t*)EEPROM_ADDR_I2C_ADRESSE, DEFAULT_I2C_ADRESSE);  // I2C-Adresse
  delay(5);
  eeprom_write_word((uint16_t*)EEPROM_ADDR_PULSE_MIN, DEFAULT_PULSE_MIN);  // PulseMin (0x05, 0x06)
  delay(5);
  eeprom_write_word((uint16_t*)EEPROM_ADDR_PULSE_MAX, DEFAULT_PULSE_MAX);  // PulseMax (0x07, 0x08)
  delay(5);

  // Berechne und speichere Checksumme
  uint8_t checksum = 0;
  checksum ^= DEFAULT_START_POSITION;
  checksum ^= DEFAULT_ANFANG;
  checksum ^= DEFAULT_ENDE;
  checksum ^= DEFAULT_SPEED;
  checksum ^= DEFAULT_I2C_ADRESSE;

  checksum ^= highByte(DEFAULT_PULSE_MIN);
  checksum ^= lowByte(DEFAULT_PULSE_MIN);

  checksum ^= highByte(DEFAULT_PULSE_MAX);
  checksum ^= lowByte(DEFAULT_PULSE_MAX);

  eeprom_write_byte((uint8_t*)EEPROM_ADDR_CHECKSUM, checksum);
  delay(5);

  // ==============================================
  // Werte aus dem EEPROM lesen und prüfen
  // ==============================================

  // Werte erneut aus dem EEPROM laden
  uint8_t eeprom_start = eeprom_read_byte((uint8_t*)EEPROM_ADDR_START_POSITION);
  uint8_t eeprom_anfang = eeprom_read_byte((uint8_t*)EEPROM_ADDR_ANFANG);
  uint8_t eeprom_ende = eeprom_read_byte((uint8_t*)EEPROM_ADDR_ENDE);
  uint8_t eeprom_speed = eeprom_read_byte((uint8_t*)EEPROM_ADDR_SPEED);
  uint8_t eeprom_i2c = eeprom_read_byte((uint8_t*)EEPROM_ADDR_I2C_ADRESSE);
  uint16_t eeprom_pmin = eeprom_read_word((uint16_t*)EEPROM_ADDR_PULSE_MIN);
  uint16_t eeprom_pmax = eeprom_read_word((uint16_t*)EEPROM_ADDR_PULSE_MAX);
  uint8_t eeprom_Checksum = eeprom_read_byte((uint8_t*)EEPROM_ADDR_CHECKSUM);

  // Neue Checksumme aus den gelesenen Werten berechnen
  uint8_t calcChecksum = 0;
  calcChecksum ^= eeprom_start;
  calcChecksum ^= eeprom_anfang;
  calcChecksum ^= eeprom_ende;
  calcChecksum ^= eeprom_speed;
  calcChecksum ^= eeprom_i2c;
  calcChecksum ^= highByte(eeprom_pmin);
  calcChecksum ^= lowByte(eeprom_pmin);
  calcChecksum ^= highByte(eeprom_pmax);
  calcChecksum ^= lowByte(eeprom_pmax);

  if (calcChecksum == eeprom_Checksum && checksum == eeprom_Checksum) {
    // Wenn alles OK dann LED an
    VPORTA.OUT |= PIN3_bm;
  } else {
    // Wenn Fehler dann LED blinkt
    while (1) {
      VPORTA.OUT ^= PIN3_bm;
      delay(250);
    }
  }
}

void loop() {
  // Keine Logik im Loop, da nur einmaliges Setzen der Standardwerte benötigt wird
}
