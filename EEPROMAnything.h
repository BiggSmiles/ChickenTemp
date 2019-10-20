//save as EEPROMAnything.h
#include <EEPROM.h>
#include <Arduino.h>  // for type definitions

template <class T> int EEPROM_writeAnything(int ee, const T& value)
{
	const byte* p = (const byte*)(const void*)&value;
	unsigned int i;
	for (i = 0; i < sizeof(value); i++) {
		const byte b = *p;
		if (eeprom_read_byte((uint8_t*)ee) != b)
			eeprom_write_byte((uint8_t*)ee++, b), ++p;
		else
			ee++, p++;
	}
}

template <class T> int EEPROM_readAnything(int ee, T& value)
{
	byte* p = (byte*)(void*)&value;
	unsigned int i;
	for (i = 0; i < sizeof(value); i++)
		*p++ = EEPROM.read(ee++);
	return i;
}
