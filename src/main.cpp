#include <Arduino.h>
#include <EEPROM.h>
#include <LowPower.h>
#include "main.h"

uint32_t sr04_pulse = 0;
uint32_t sr04_dist = 0;

bool     object_present = false;
uint16_t object_count = 0;
uint16_t object_total_count = 0;

uint32_t slept_time_ms = 0;
uint32_t reset_after = 51000000; // 24 hours

void setup()
{
	Serial.begin(SERIAL_BAUD);
	while (!Serial)
		;

	EEPROM_INIT;

	object_total_count = EEPROM_GET;
	Serial.print(F("Total count is "));
	Serial.println(object_total_count);

	SR04_INIT;
	DISPLAY_INIT;
	DISPLAY_OFF;
}

uint16_t getDistance() {
	SR04_POWER_ON;
	SR04_TRIG;
	sr04_pulse = SR04_DIST;
	SR04_POWER_OFF;
	return sr04_pulse * 0.034 / 2;
}

uint16_t displayNumber(uint8_t addr, uint16_t a) {
	a = a % 10000;
	uint8_t blank = 0xf;
	uint16_t d = a ;
	if (a > 999) {
		a = a % 1000;
		d = (d - a) / 1000;
		DISPLAY_SHIFT(addr--, d);	
		blank = 0;
		d = a;
	} else {
		DISPLAY_SHIFT(addr--, blank);	
	}

	if (a > 99) {
		a = a % 100;
		d = (d - a) / 100;
		DISPLAY_SHIFT(addr--, d);	
		blank = 0;
		d = a;
	} else {
		DISPLAY_SHIFT(addr--, blank);	
	}

	if (a > 9) {
		a = a % 10;
		d = (d - a) / 10;
		DISPLAY_SHIFT(addr--, d);	
		blank = 0;
		d = a;
	} else {
		DISPLAY_SHIFT(addr--, blank);	
	}

	if (a > 0) {
		DISPLAY_SHIFT(addr--, a);	
	} else {
		DISPLAY_SHIFT(addr--, blank);	
	}
}

void displayNumbers(uint16_t a, uint16_t b) {
	displayNumber(0x4, b);
	displayNumber(0x8, a);
}

void loop()
{
	// reset every 24 hours
	uint32_t ms = millis() + slept_time_ms;
	if (ms > reset_after) {
		Serial.print(F("resetting..."));
		SELF_RESET; 
	}

	uint16_t dist = getDistance();
	#ifdef DEBUG
	Serial.println(dist);
	delay(1);
	#endif

	if (dist < SR04_THRESHOLD) {
		if (!object_present) {
			//Serial.println(F("obj in sight"));
			object_present = true;
			object_count++;
			object_total_count++;
			// show number
			DISPLAY_ON;
			EEPROM_SET(object_total_count);
			#ifdef DEBUG
			displayNumbers(object_count, dist);
			#else
			displayNumbers(object_count, object_total_count);
			#endif
			
			slept_time_ms += 500;
			LowPower.powerDown(SLEEP_500MS, ADC_OFF, BOD_OFF);
		}
	} else {
		if (object_present) {
			object_present = false;
			//Serial.println(F("obj left"));
			
			DISPLAY_OFF;
		}
	}

	slept_time_ms += 500;
	LowPower.powerDown(SLEEP_500MS, ADC_OFF, BOD_OFF);

}