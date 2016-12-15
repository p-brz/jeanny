/* Create a WiFi access point and provide a web server on it. */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "pins.h"
#include "game.h"

Game game(1);

void setupInterface(){
    for(int i=0;i < 3; ++i){
        pinMode(buttonsPins[i], INPUT);
        pinMode(ledPins[i], OUTPUT);
    }
}

void setup() {
	delay(5000);
	Serial.begin(115200);

	setupInterface();
}

void loop() {
    game.runState();
}
