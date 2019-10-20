# ChickenTemp
This code uses the TouchOSC app to control a relay. Whick in my case controls a Heat lamp.

This function will setup the environment for the relay operation.

		msgIN.route("/1/fader1", LowTemp);          Sets the low temp for activation of relay
			msgIN.route("/1/fader2", HighTemp);       Sets the high temp for activation of relay
			msgIN.route("/1/push1", resetOnce);   
			msgIN.route("/1/push2", TestON);          Turn the relay on for a test
			msgIN.route("/1/push3", TestOFF);         Turns the relay off for a test
			msgIN.route("/1/btnsavetemps", SaveTemps); Saves currect settings for the control temperatures
			////