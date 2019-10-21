// ESP8266 DS18B20 ArduinoIDE Thingspeak IoT Example code

#include <EEPROM.h>
#include <SLIPEncodedUSBSerial.h>
#include <SLIPEncodedSerial.h>
#include <OSCTiming.h>
#include <OSCMessage.h>
#include <OSCMatch.h>
#include <OSCData.h>
#include <OSCBundle.h>
#include <OSCBoards.h>

#include <WiFiUdp.h>
#include <WiFiServer.h>
#include <WiFiClientSecure.h>
#include <WiFiClient.h>

#include <ESP8266WiFiType.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFi.h>

#include <DallasTemperature.h>


#define ONE_WIRE_BUS D1
#define LIGHT D2
bool updatePhoneOnlyIfSomethingChanges = false;
bool testMode = false;
bool onOnce = false;
bool offOnce = false;
float tempON = 32;
float tempOFF = 33;
float temperature = 999;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);


/*																*/
/*  receive all touchOSC mesage values here						*/
/*																*/
int  valueIn = 0;	// recieved from touchOSCX msg
OSCMessage msgIN;  //all TouchOSC messages are recieved here 

					/*																			*/
					/*   using a UDP server to communicate to TouchOSC for ScoreBoard activity */
					/*																			*/
WiFiUDP Udp;
int serverPort = 8000; //from Iphone TouchOSC (incoming port)
int destPort = 9000;    //To iphone TouchOSC (outgoing port)

char temperatureString[6];

void setup(void) {
	Serial.begin(115200);
	Serial.println("");
	pinMode(LIGHT, OUTPUT); //Declare Pin mode

	WiFi.mode(WIFI_AP_STA);
	delay(110);
	//
	//  Start UDP server
	//

	Udp.begin(serverPort);
	//delay(1000);
	OSCMsgReceive();

	oscUpdateLabel("/1/label8", "Start UDP server");


	DS18B20.begin();
	EEPROM.begin(4);
	tempON = int(EEPROM.read(0));
	tempOFF = int(EEPROM.read(1));
	oscUpdateButton("/1/fader1", byte(tempON));
	oscUpdateButton("/1/fader2", byte(tempOFF));

	char str10[10];
	sprintf(str10, "%.0f", tempOFF);
	oscUpdateLabel("/1/label5", str10);  // cut off temperature

	sprintf(str10, "%.0f", tempON);
	oscUpdateLabel("/1/label3", str10);  // cut off temperature

}

float getTemperature() {
	float temp;
	static float SaveTemp;
	do {
		DS18B20.requestTemperatures();
		//	temp = DS18B20.getTempCByIndex(0);
		temp = DS18B20.getTempFByIndex(0);
		delay(100);
	} while (temp == 120.0 || temp == (-30.0));

	if (SaveTemp != temp)
		{
		bool updatePhoneOnlyIfSomethingChanges = false;
		SaveTemp = temp;
		}
	return temp;
}


void loop() {
	temperature = getTemperature();
	OSCMsgReceive();     /* Check for TouchOSC messages */
	UpdatePhone();

	if (testMode) { return; }
	oscUpdateLabel("/1/label8", "Test Mode OFF");
	if (temperature > tempON) {
		if (!offOnce) {
		//	Serial.println("Turn OFF Light");
			offOnce = true; onOnce = false; 
			digitalWrite(LIGHT, HIGH);
			
			oscUpdateLabel("/1/label8", "Light OFF");
		}
	}
	if (temperature < tempOFF) {
		if (!onOnce) {
			//Serial.println("Turn ON Light");
			onOnce = true;
			offOnce = false; 
			digitalWrite(LIGHT, LOW);
			oscUpdateLabel("/1/label8", "Light ON");
		}
	}
	

}

void OSCMsgReceive() {
	OSCMessage msgIN;
	int size;
	if ((size = Udp.parsePacket()) > 0) {
		while (size--)
			msgIN.fill(Udp.read());
		if (!msgIN.hasError()) {
			valueIn = msgIN.getFloat(0);
			//oscUpdateLabel(p1_lblstatus2_addr, p1_lblstatus2_txt);   // reset the lbstatus2 label in touchosc socreboard

			msgIN.route("/1/fader1", LowTemp);
			msgIN.route("/1/fader2", HighTemp);
			msgIN.route("/1/push1", resetOnce);
			msgIN.route("/1/push2", TestON);
			msgIN.route("/1/push3", TestOFF);
			msgIN.route("/1/btnsavetemps", SaveTemps);
		}
	}
}

void SaveTemps(OSCMessage &msg, int addrOffset)
{
	Serial.print("save Temp ON: "); Serial.println(int(tempON));
	Serial.print("Temp OFF: "); Serial.println(tempOFF);
	updatePhoneOnlyIfSomethingChanges = true;
	EEPROM.begin(4);
	EEPROM.write(0, int(tempON));
	EEPROM.write(1, int(tempOFF));
	EEPROM.commit();
	oscUpdateButton("/1/btnsavetemps", 1);
	Serial.println("Waiting 10 seconds...");

EEPROM.end();
	Serial.println("Reading EEPROM");
	Serial.println("");

//	tempON = int(EEPROM.read(0));
//	tempOFF = int(EEPROM.read(1));
//	Serial.print("after save Temp ON: "); Serial.println(int(tempON));
//	Serial.print("Temp OFF: "); Serial.println(tempOFF);

}
void TestON(OSCMessage &msg, int addrOffset)
{
	if (!msg.isFloat(0)) { Serial.print("LowTemp not valid: "); Serial.println(valueIn);
	oscUpdateLabel("/1/label8", "Light ON - failed"); 
	return; }
	testMode = true;
	updatePhoneOnlyIfSomethingChanges = true;
	digitalWrite(LIGHT, LOW);
	oscUpdateLabel("/1/label8", "Light ON");

}
void TestOFF(OSCMessage &msg, int addrOffset)
{
	if (!msg.isFloat(0)) { Serial.print("LowTemp not valid: ");       Serial.println(valueIn);
	   oscUpdateLabel("/1/label8", "Light OFF - failed");
	    return;
	}
	testMode = false;
	updatePhoneOnlyIfSomethingChanges = true;
	digitalWrite(LIGHT, HIGH);
	oscUpdateLabel("/1/label8", "Light OFF");

}

void LowTemp(OSCMessage &msg, int addrOffset)
{
	if (!msg.isFloat(0)) { oscUpdateLabel("/1/label8", "Set LOW temp Failed"); return; }
	updatePhoneOnlyIfSomethingChanges = true;
	tempON = valueIn;
	oscUpdateLabel("/1/label8", "Set LOW Temp");
	oscUpdateButton("/1/btnsavetemps", 0);
}

void HighTemp(OSCMessage &msg, int addrOffset)
{
	if (!msg.isFloat(0)) { oscUpdateLabel("/1/label8", "Set HIGH temp Failed"); return; }
	updatePhoneOnlyIfSomethingChanges = true;
	tempOFF = valueIn;
	oscUpdateLabel("/1/label8", "Set HIGH Temp");
	oscUpdateButton("/1/btnsavetemps", 0);
}

void resetOnce(OSCMessage &msg, int addrOffset)
{
	if (!msg.isFloat(0)) { oscUpdateLabel("/1/label8", "Reset Failed"); return; }
	updatePhoneOnlyIfSomethingChanges = true;
	offOnce = false;
	onOnce = false;
	oscUpdateLabel("/1/label8", "Do Reset of Once switches");
}

void UpdatePhone()
{
	if (!updatePhoneOnlyIfSomethingChanges) {
		return;
		}
	updatePhoneOnlyIfSomethingChanges = false;
	char str10[10];
	static float lasttempON;
	static float lasttempOFF;
	static float lasttemperature;

	if (lasttemperature != temperature) {
		sprintf(str10, "%.0f", temperature);
		oscUpdateLabel("/1/label7", str10);  // current tremp
		lasttemperature = temperature;
		}
	if (lasttempOFF != tempOFF) {
		sprintf(str10, "%.0f", tempOFF);
		oscUpdateLabel("/1/label5", str10);  // cut off temperature
		lasttempOFF = tempOFF;
		}
	if (lasttempON != tempON) {
		sprintf(str10, "%.0f", tempON);
		oscUpdateLabel("/1/label3", str10);  // cut off temperature
		lasttempON = tempON;
		}
	// labbel  3 low temp on. 5 = higfh temp off, 7 = current temp

}
void oscUpdateButton(char * adr, byte v)
{
	OSCMessage msgBtn(adr);
	msgBtn.add(v);
	Udp.beginPacket(Udp.remoteIP(), destPort);
	msgBtn.send(Udp); // send the bytes
	Udp.endPacket(); // mark the end of the OSC Packet
	msgBtn.empty(); // free space occupied by message
//	delay(120);
}
void oscUpdateLabel(char * adr, char value[])
{
	OSCMessage msgLbl(adr);
	msgLbl.add(value);
	Udp.beginPacket(Udp.remoteIP(), destPort);
	msgLbl.send(Udp); // send the bytes
	Udp.endPacket(); // mark the end of the OSC Packet
	msgLbl.empty(); // free space occupied by message
	msgIN.empty();
//	delay(10);
}