/* Create a WiFi access point and provide a web server on it. */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "pins.h"
#include "game.h"

Game game(1);

void setupInterface(){
    for(int i=0;i < 2; ++i){
        pinMode(buttonsPins[i], INPUT);
        pinMode(ledPins[i], OUTPUT);
    }
}

void setup() {
	Serial.begin(115200);
	setupInterface();
}

void loop() {
    // Serial.println("- Running main loop");
    game.runState();
}
