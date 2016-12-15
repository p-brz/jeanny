/* Create a WiFi access point and provide a web server on it. */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "network.h"

#include "pins.h"
#include "game.h"

Network peer;
Game game(&peer);

void setupInterface(){
    for(int i=0;i < 2; ++i){
        pinMode(buttonsPins[i], INPUT);
        pinMode(ledPins[i], OUTPUT);
    }
}

void setup() {
    delay(5000);
    
	Serial.begin(115200);
	setupInterface();
	
	pinMode(jumperPin, INPUT);
	if(digitalRead(jumperPin)){
        game.setIsServer(true);
        peer.setupServer();
        
        game.changeState(State::waitPlayer);
	}else{
        game.setIsServer(false);
        peer.setupClient();
        
        game.changeState(State::waitTurn);
	}
}

void loop() {
//    Serial.println("- Running main loop");
    
    game.runState();
}
