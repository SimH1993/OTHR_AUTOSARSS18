# RTE Funktionen für LEDs

Stellt die RTE Funktionen für das Ansteuern der LEDs über I2C zur Verfügung.

## Defines zu setzen

#define LED_EXTERN --> Schaltet den Code für die Ansteuerung der LEDs ein
#define DIO_EXTERN --> Schaltet die Logik für externe DIO-Geräte ein

#define LED_I2C_PORT NXT_PORT_S1 --> Setzt den Port, an dem der I2C Expander angschlossen ist
#define LED_I2C_ADRESS 0x20 --> Setzt die Adresse des I2C Expander
#define LED_NUMBER_OF_LEDS 4 --> Setzt Anzahl der angeschlossenen LEDs

