#ifndef SERIAL_BAUD
#define SERIAL_BAUD 115200
#endif

// #define DEBUG

#ifdef DEBUG
#define PIN_SR04_POW_LED 13
#endif

#define PIN_SR04_POW 4
#define PIN_SR04_TRIG 3
#define PIN_SR04_ECHO 2
#define SR04_THRESHOLD 50

#ifdef PIN_SR04_POW_LED
#define POW_LED_INIT pinMode(PIN_SR04_POW_LED, OUTPUT)
#define POW_LED_ON digitalWrite(PIN_SR04_POW_LED, HIGH)
#define POW_LED_OFF digitalWrite(PIN_SR04_POW_LED, LOW)
#else
#define POW_LED_INIT
#define POW_LED_ON
#define POW_LED_OFF
#endif

#define SR04_INIT                   \
    pinMode(PIN_SR04_POW, OUTPUT);  \
    POW_LED_INIT;                   \
    pinMode(PIN_SR04_TRIG, OUTPUT); \
    pinMode(PIN_SR04_ECHO, INPUT);

#define SR04_POWER_ON                 \
    pinMode(PIN_SR04_POW, OUTPUT);    \
    digitalWrite(PIN_SR04_POW, HIGH); \
    POW_LED_ON;                       \
    delay(100);

#define SR04_POWER_OFF               \
    digitalWrite(PIN_SR04_POW, LOW); \
    pinMode(PIN_SR04_POW, INPUT);    \
    POW_LED_OFF;                     \
    delay(1);

#define SR04_TRIG                      \
    digitalWrite(PIN_SR04_TRIG, LOW);  \
    delayMicroseconds(2);              \
    digitalWrite(PIN_SR04_TRIG, HIGH); \
    delayMicroseconds(10);             \
    digitalWrite(PIN_SR04_TRIG, LOW);

#define SR04_DIST \
    pulseIn(PIN_SR04_ECHO, HIGH) - 10;

#define PIN_DISPLAY_CS 10
#define PIN_DISPLAY_CLK 12
#define PIN_DISPLAY_DATA 11 
#define DISPLAY_BRIGHTNESS 0x02 // 0x00 .. 0x0f

#define DISPLAY_SHIFT(addr, data)                                \
    digitalWrite(PIN_DISPLAY_CS, LOW);                           \
    shiftOut(PIN_DISPLAY_DATA, PIN_DISPLAY_CLK, MSBFIRST, addr); \
    shiftOut(PIN_DISPLAY_DATA, PIN_DISPLAY_CLK, MSBFIRST, data); \
    digitalWrite(PIN_DISPLAY_CS, HIGH);

// 0x0f, 0x00 display test register - test mode off */ \ 
// 0x0c  shutdown register  */ \ 
//      0x00 - shutdown
//      0x01 - normal operation
// 0x0b, 0x07 scan limit register - display digits 0 thru 7*/ \ 
// 0x0a, 0x0f intensity register - max brightness */ \ 
// 0x09, 0xff decode mode register - CodeB decode all digits */

#define DISPLAY_INIT                     \
    pinMode(PIN_DISPLAY_DATA, OUTPUT);   \
    pinMode(PIN_DISPLAY_CS, OUTPUT);     \
    pinMode(PIN_DISPLAY_CLK, OUTPUT);    \
    digitalWrite(PIN_DISPLAY_CLK, HIGH); \
    delay(200);                          \
    DISPLAY_SHIFT(0x0f, 0x00);           \
    DISPLAY_SHIFT(0x09, 0xff);           \
    DISPLAY_SHIFT(0x0b, 0x07);           \
    DISPLAY_SHIFT(0x0a, DISPLAY_BRIGHTNESS);

#define DISPLAY_ON \
    DISPLAY_SHIFT(0x0c, 0x01);

#define DISPLAY_OFF \
    DISPLAY_SHIFT(0x0c, 0x00);

#define EEPROM_RESET_VALUE 0
#define EEPROM_RESET_FLAG_ADDR 0x00
#define EEPROM_RESET_FLAG_VAL 0xAB
#define EEPROM_TOTAL_ADDR 0x01

#define EEPROM_GET \
    EEPROM.read(EEPROM_TOTAL_ADDR + 0) + (EEPROM.read(EEPROM_TOTAL_ADDR + 1) << 8);

#define EEPROM_SET(value)                              \
    EEPROM.write(EEPROM_TOTAL_ADDR + 0, value & 0xff); \
    EEPROM.write(EEPROM_TOTAL_ADDR + 1, (value >> 8) & 0xff);

#define EEPROM_RESET \
    EEPROM_SET(EEPROM_RESET_VALUE)

#define EEPROM_INIT                                                   \
    if (EEPROM.read(EEPROM_RESET_FLAG_ADDR) != EEPROM_RESET_FLAG_VAL) \
    {                                                                 \
        EEPROM_RESET;                                                 \
        EEPROM.write(EEPROM_RESET_FLAG_ADDR, EEPROM_RESET_FLAG_VAL);  \
    }

#define PIN_SELF_RESET 5

#define SELF_RESET                   \
    pinMode(PIN_SELF_RESET, OUTPUT); \
    digitalWrite(PIN_SELF_RESET, HIGH);