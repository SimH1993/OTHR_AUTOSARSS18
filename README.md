# RTE Funktionen für LEDs

Stellt die RTE Funktionen für das Ansteuern der LEDs über I2C zur Verfügung.

## Defines zu setzen im Codegenerator

### Schalte den Code für die Ansteuerung der LEDs ein

#define LED_EXTERN

### Schalte die Logik für externe DIO-Geräte ein

#define DIO_EXTERN

### Setze den NXT-Port für I2C

#define LED_I2C_PORT NXT_PORT_S1

### Setze Adresse des I2C Expanders

#define LED_I2C_ADRESS 0x20

### Setze die Anzahl der angeschlossenen LEDs

#define LED_NUMBER_OF_LEDS 4

## RTE-Funktionen

void RTE_INIT_DIO_INTERFACE();

void RTE_DINIT_DIO_INTERFACE();

void RTE_DIO_READ_DATA(DIO_Devices device);

void RTE_DIO_WRITE_DATA(DIO_Devices device, DATA_TO_SEND dataToSend);

