/*
*
* Read and write demo of the AT24CX library
* Written by Christian Paul, 2014-11-24
* https://github.com/cyberp/AT24Cx
*
*/


// setup
void I2C_Eeprom_Setup() {
	if (eepSettings.debugEeprom) { Serial.println("\nI2C_Eeprom_Setup()"); }

	AT24CX(1, 256);
	if (eepSettings.debugEeprom) {
		Serial.println("AT24CX read/write demo");
		Serial.println("----------------------");
		Serial.print("AT24C32 DEC Addr: "); Serial.println(AT24CX_ID, DEC);
		Serial.print("AT24C32 HEX Addr: "); Serial.println(AT24CX_ID, HEX);
		Serial.print("AT24C32 BIN Addr: "); Serial.println(AT24CX_ID, BIN);
		Serial.println("----------------------\n");
	}
}



void fetchEepromValues() {
	//
	// from eeprom or esp8266 flash memory
	//   address if 0x57
	//  read the information from the AT24C32 and store in eepSeeting struct
	//
	if (eepSettings.debugEeprom) { Serial.println("fetchEepromValues() - begin fetch"); }
	String str = "";
	char m[10];

	eepSettings.Zone = mem.readInt(sZone);
	eepSettings.setDate = mem.read(ssetDate);
	eepSettings.setDate2 = mem.read(ssetDate2);
	eepSettings.dowIn = mem.read(sdowIn);
	eepSettings.firstMeetingDayNumber = mem.read(sfirstMeetingDayNumber);
	eepSettings.secondMeetingDayNumber = mem.read(ssecondMeetingDayNumber);
	eepSettings.TOD_Sign2_ON_Hour = mem.read(sTOD_Sign2_ON_Hour);
	eepSettings.TOD_Sign2_ON_Minutes = mem.read(sTOD_Sign2_ON_Minutes);
	eepSettings.TOD_Sign2_OFF_Hour = mem.read(sTOD_Sign2_OFF_Hour);
	eepSettings.TOD_Sign2_OFF_Minutes = mem.read(sTOD_Sign2_OFF_Minutes);

	eepSettings.TOD_Sign_ON_Hour = mem.read(sTOD_Sign_ON_Hour);
	eepSettings.TOD_Sign_ON_Minutes = mem.read(sTOD_Sign_ON_Minutes);
	eepSettings.TOD_Sign_OFF_Hour = mem.read(sTOD_Sign_OFF_Hour);
	eepSettings.TOD_Sign_OFF_Minutes = mem.read(sTOD_Sign_OFF_Minutes);

	eepSettings.FirstEepromSetup = mem.read(sFirstEepromSetup);
	eepSettings.debug = mem.read(sdebug);
	eepSettings.debugEeprom = mem.read(sdebugEeprom);
	eepSettings.debugLoop = mem.read(sdebugLoop);
	eepSettings.debugRTC = mem.read(sdebugRTC);
	eepSettings.hour = mem.read(shour);
	eepSettings.minutes = mem.read(sminutes);
	eepSettings.seconds = mem.read(sseconds);
	eepSettings.month = mem.read(smonth);
	eepSettings.day = mem.read(sday);
	eepSettings.year = mem.readInt(syear);
	eepSettings.signTest = mem.read(ssigntest);
	eepSettings.alarmHour = mem.read(salarmHour);
	eepSettings.alarmMinutes = mem.read(salarmMinutes);
	eepSettings.debugLightTest = mem.read(sdebugLightTest);
	eepSettings.dayLightSavesChange = mem.read(sdayLightSavesChange);

	mem.readChars(sfirstMeetingDate, m, sizeof(m));
	str = m;
	eepSettings.firstMeetingDate = str;
	mem.readChars(ssecondMeetingDate, m, sizeof(m));
	str = m;
	eepSettings.secondMeetingDate = str;
	if (eepSettings.debugEeprom) {
		 printEepsettings("Fetched data");
		 Serial.println("fetchEepromValues() - end fetch");
	}
}



void storeValuesToEeprom() {
	if (eepSettings.debugEeprom) { Serial.println("\nstoreValuesToEeprom() - begin store"); }

	int si = 0;
	byte b = 0;
	char m[10];  //used for dates
	String str = "";

	si = mem.readInt(sZone);		// zone
	if (si != eepSettings.Zone) { mem.writeInt(sZone, eepSettings.Zone); }

	delay(1);
	b = mem.read(ssetDate);
	if (b != eepSettings.setDate) { mem.write(ssetDate, eepSettings.setDate); }
	delay(1);
	b = mem.read(ssetDate2);
	if (b != eepSettings.setDate2) { mem.write(ssetDate2, eepSettings.setDate2); }
	delay(1);
	b = mem.read(sdowIn);
	if (b != eepSettings.dowIn) { mem.write(sdowIn, eepSettings.dowIn); }
	delay(1);
	b = mem.read(sfirstMeetingDayNumber);
	if (b != eepSettings.firstMeetingDayNumber) { mem.write(sfirstMeetingDayNumber, eepSettings.firstMeetingDayNumber); }
	delay(1);
	b = mem.read(ssecondMeetingDayNumber);
	if (b != eepSettings.secondMeetingDayNumber) { mem.write(ssecondMeetingDayNumber, eepSettings.secondMeetingDayNumber); }
	delay(1);
	b = mem.read(sTOD_Sign2_ON_Hour);
	if (b != eepSettings.TOD_Sign2_ON_Hour) { mem.write(sTOD_Sign2_ON_Hour, eepSettings.TOD_Sign2_ON_Hour); }
	delay(1);
	b = mem.read(sTOD_Sign2_ON_Minutes);
	if (b != eepSettings.TOD_Sign2_ON_Minutes) { mem.write(sTOD_Sign2_ON_Minutes, eepSettings.TOD_Sign2_ON_Minutes); }
	delay(1);
	b = mem.read(sTOD_Sign2_OFF_Hour);
	if (b != eepSettings.TOD_Sign2_OFF_Hour) { mem.write(sTOD_Sign2_OFF_Hour, eepSettings.TOD_Sign2_OFF_Hour); }
	delay(1);
	b = mem.read(sTOD_Sign2_OFF_Minutes);
	if (b != eepSettings.TOD_Sign2_OFF_Minutes) { mem.write(sTOD_Sign2_OFF_Minutes, eepSettings.TOD_Sign2_OFF_Minutes); }
	delay(1);
	b = mem.read(sTOD_Sign_ON_Hour);
	if (b != eepSettings.TOD_Sign_ON_Hour) { mem.write(sTOD_Sign_ON_Hour, eepSettings.TOD_Sign_ON_Hour); }
	delay(1);
	b = mem.read(sTOD_Sign_ON_Minutes);
	if (b != eepSettings.TOD_Sign_ON_Minutes) { mem.write(sTOD_Sign_ON_Minutes, eepSettings.TOD_Sign_ON_Minutes); }
	delay(1);
	b = mem.read(sTOD_Sign_OFF_Hour);
	if (b != eepSettings.TOD_Sign_OFF_Hour) { mem.write(sTOD_Sign_OFF_Hour, eepSettings.TOD_Sign_OFF_Hour); }
	delay(1);
	b = mem.read(sTOD_Sign_OFF_Minutes);
	if (b != eepSettings.TOD_Sign_OFF_Minutes) { mem.write(sTOD_Sign_OFF_Minutes, eepSettings.TOD_Sign_OFF_Minutes); }
	delay(1);
	b = mem.read(sFirstEepromSetup);
	if (b != eepSettings.FirstEepromSetup) { mem.write(sFirstEepromSetup, eepSettings.FirstEepromSetup); }
	delay(1);
	b = mem.read(sdebug);
	if (b != eepSettings.debug) { mem.write(sdebug, eepSettings.debug); }
	delay(1);
	b = mem.read(sdebugEeprom);
	if (b != eepSettings.debugEeprom) { mem.write(sdebugEeprom, eepSettings.debugEeprom); }
	delay(1);
	b = mem.read(sdebugLoop);
	if (b != eepSettings.debugLoop) { mem.write(sdebugLoop, eepSettings.debugLoop); }
	delay(1);
	b = mem.read(sdebugRTC);
	if (b != eepSettings.debugRTC) { mem.write(sdebugRTC, eepSettings.debugRTC); }
	b = mem.read(smonth);
	if (b != eepSettings.month) { mem.write(smonth, eepSettings.month); }
	delay(1);
	b = mem.read(sday);
	if (b != eepSettings.day) { mem.write(sday, eepSettings.day); }
	delay(1);
	b = mem.read(shour);
	if (b != eepSettings.hour) { mem.write(shour, eepSettings.hour); }
	delay(1);
	b = mem.read(sminutes);
	if (b != eepSettings.minutes) { mem.write(sminutes, eepSettings.minutes); }
	delay(1);
	b = mem.read(sseconds);
	if (b != eepSettings.seconds) { mem.write(sseconds, eepSettings.seconds); }
	delay(1);

	b = mem.read(ssigntest);
	if (b != eepSettings.signTest) { mem.write(ssigntest, eepSettings.signTest); }
	delay(1);
	b = mem.read(salarmHour);
	if (b != eepSettings.alarmHour) { mem.write(salarmHour, eepSettings.alarmHour); }
	delay(1);
	b = mem.read(salarmMinutes);
	if (b != eepSettings.alarmMinutes) { mem.write(salarmMinutes, eepSettings.alarmMinutes); }
	delay(1);
	b = mem.read(sdebugLightTest);
	if (b != eepSettings.debugLightTest) { mem.write(sdebugLightTest, eepSettings.debugLightTest); }
	delay(1);
	b = mem.read(sdayLightSavesChange);
	if (b != eepSettings.dayLightSavesChange) { mem.write(sdayLightSavesChange, eepSettings.dayLightSavesChange); }
	delay(1);
	
	si = mem.readInt(syear);		// zone
	if (si != eepSettings.year) { mem.writeInt(syear, eepSettings.year); }

	mem.readChars(sfirstMeetingDate, m, sizeof(m));
	str = m;
	if (str != eepSettings.firstMeetingDate)
	{
		strcpy(m, eepSettings.firstMeetingDate.c_str());
		mem.writeChars(sfirstMeetingDate, m, sizeof(m));
	}
	mem.readChars(ssecondMeetingDate, m, sizeof(m));
	str = m;
	if (str != eepSettings.secondMeetingDate)
	{
		strcpy(m, eepSettings.secondMeetingDate.c_str());
		mem.writeChars(ssecondMeetingDate, m, sizeof(m));
	}
	strcpy(m, eepSettings.secondMeetingDate.c_str());
	mem.writeChars(ssecondMeetingDate, m, sizeof(m));

	delay(1);
	if (eepSettings.debugEeprom) { Serial.println("storeValuesToEeprom() - end store"); }
}


void setupInitialEepSettings()
{
	int Zone = -6;					// time zone offset -5 est and -6 dst
	eepSettings.FirstEepromSetup = 1;		// if 0 then eeprom initializtion occurrs

	eepSettings.setDate = 0;		// if true will set to compile date
	eepSettings.setDate2 = 0;		// if true will set to coded date
	eepSettings.dowIn = 0;					// day of week for meeting
	eepSettings.firstMeetingDayNumber = 2;		// first meeting of month
	eepSettings.secondMeetingDayNumber = 4;		// second meeting of month
	eepSettings.TOD_Sign2_ON_Hour = 0;	   // Time of day to turn sign2 light on
	eepSettings.TOD_Sign2_ON_Minutes = 0;   // Time of day to turn sign2 light on
	eepSettings.TOD_Sign2_OFF_Hour = 0;	   // Time of day to turn sign2 light off
	eepSettings.TOD_Sign2_OFF_Minutes = 0;   // Time of day to turn sign2 light off
	eepSettings.TOD_Sign_ON_Hour = 12;		  // Time of day to turn Sign light on
	eepSettings.TOD_Sign_ON_Minutes = 4;	  // Time of day to turn Sign light on
	eepSettings.TOD_Sign_OFF_Hour = 12;	  // Time of day to turn Sign light off
	eepSettings.TOD_Sign_OFF_Minutes = 5;   // Time of day to turn Sign light off
	eepSettings.debug = 0;				// set to  0 for off and 1 for on
	eepSettings.debugEeprom = 0;			// set to  0 for off and 1 for on
	eepSettings.debugLoop = 0;			// set to  0 for off and 1 for on
	eepSettings.debugRTC = true;			// set to  0 for off and 1 for on
	eepSettings.month = 12;
	eepSettings.day = 21;
	eepSettings.year = 2017;
	eepSettings.hour = 19;
	eepSettings.minutes = 30;
	eepSettings.seconds = 10;
	eepSettings.signTest = true;
	eepSettings.firstMeetingDate = "20171207";	// yyyymmdd - set in function: SetMeetingDate()
	eepSettings.secondMeetingDate = "20171221";	// yyyymmdd - set in function: SetMeetingDate()
	eepSettings.hour = 19;  // last saved hour
	eepSettings.minutes = 42;  // last saved minutes
	eepSettings.seconds = 30;  // last saved seconds
	eepSettings.month = 12;  // last saved month
	eepSettings.day = 21;  // last saved day
	eepSettings.year = 2017;  // last saved year
	eepSettings.alarmHour = 0;  // Manual Sign light test
	eepSettings.alarmMinutes = 0;  // Manual Sign light test
	eepSettings.debugLightTest = 0;  // Manual Sign light test
	eepSettings.dayLightSavesChange = false;  // Manual Sign light test


}
void printEepsettings(String s)
{
	Serial.println(""); Serial.println(s); Serial.println("");
	Serial.print("Zone: "); Serial.println(eepSettings.Zone);
	Serial.print("setDate: "); Serial.println(eepSettings.setDate);
	Serial.print("setDate2: "); Serial.println(eepSettings.setDate2);
	Serial.print("dowIn: "); Serial.println(eepSettings.dowIn);
	Serial.print("firstMeetingDayNumber: "); Serial.println(eepSettings.firstMeetingDayNumber);
	Serial.print("secondMeetingDayNumber: "); Serial.println(eepSettings.secondMeetingDayNumber);
	Serial.print("TOD_Sign2_ON_Hour: "); Serial.println(eepSettings.TOD_Sign2_ON_Hour);
	Serial.print("TOD_Sign2_ON_Minutes: "); Serial.println(eepSettings.TOD_Sign2_ON_Minutes);
	Serial.print("TOD_Sign2_OFF_Hour: "); Serial.println(eepSettings.TOD_Sign2_OFF_Hour);
	Serial.print("TOD_Sign2_OFF_Minutes: "); Serial.println(eepSettings.TOD_Sign_OFF_Minutes);
	Serial.print("TOD_Sign_ON_Hour: "); Serial.println(eepSettings.TOD_Sign_ON_Hour);
	Serial.print("TOD_Sign_ON_Minutes: "); Serial.println(eepSettings.TOD_Sign_ON_Minutes);
	Serial.print("TOD_Sign_OFF_Hour: "); Serial.println(eepSettings.TOD_Sign_OFF_Hour);
	Serial.print("TOD_Sign_OFF_Minutes: "); Serial.println(eepSettings.TOD_Sign_OFF_Minutes);
	Serial.print("FirstEepromSetup: "); Serial.println(eepSettings.FirstEepromSetup);
	Serial.print("debug: "); Serial.println(eepSettings.debug);
	Serial.print("debugEeprom: "); Serial.println(eepSettings.debugEeprom);
	Serial.print("debugLoop: "); Serial.println(eepSettings.debugLoop);
	Serial.print("eepSettings.month: "); Serial.println(eepSettings.month);
	Serial.print("eepSettings.day: "); Serial.println(eepSettings.day);
	Serial.print("eepSettings.year: "); Serial.println(eepSettings.year);
	Serial.print("eepSettings.hour: "); Serial.println(eepSettings.hour);
	Serial.print("eepSettings.minutes: "); Serial.println(eepSettings.minutes);
	Serial.print("eepSettings.seconds: "); Serial.println(eepSettings.seconds);
	Serial.print("eepSettings.signTest: "); Serial.println(eepSettings.signTest);

	//	Serial.print("firstMeetingDate: "); Serial.println(eepSettings.firstMeetingDate);
	Serial.print("firstMeetingDate: "); Serial.println(eepSettings.firstMeetingDate);
	Serial.print("secondMeetingDate: "); Serial.println(eepSettings.secondMeetingDate);

	Serial.print("hour: "); Serial.println(eepSettings.hour);
	Serial.print("minutes: "); Serial.println(eepSettings.minutes);
	Serial.print("seconds: "); Serial.println(eepSettings.seconds);
	Serial.print("month: "); Serial.println(eepSettings.month);
	Serial.print("day: "); Serial.println(eepSettings.day);
	Serial.print("year: "); Serial.println(eepSettings.year);
	Serial.print("alarmHour: "); Serial.println(eepSettings.alarmHour);
	Serial.print("alarmMinutes: "); Serial.println(eepSettings.alarmMinutes);
	Serial.print("debugLightTest: "); Serial.println(eepSettings.debugLightTest);
	Serial.print("dayLightSavesChange: "); Serial.println(eepSettings.dayLightSavesChange);
}