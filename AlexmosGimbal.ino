/*
 Name:		AlexmosGimbal.ino
 Created:	4/24/2023 1:34:03 PM
 Author:	Imami Joel Betofe
*/

#include "MavlinkSettings.h"
#include "GimbalSettings.h"
#include "Globals.h"

Gimbal gimbal;
MavlinkConnection mavlink;
// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(DEBUG_BAUD_RATE);
	mavlink.init();
	gimbal.init();
}

// the loop function runs over and over again until power down or reset
void loop() {
	mavlink.run();
	gimbal.run();
}
