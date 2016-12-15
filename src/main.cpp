/* Create a WiFi access point and provide a web server on it. */

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

#include "network.h"
#include "game_state.h"

int jumperPin = 14;
const int buttonsPins[] = {14, 12};
const int ledPins[] = {5, 4};

bool isServer = false;
int difficultLevel = 0;

State currentState;

Network peer;

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
	
	pinMode(jumperPin, INPUT);
	if(digitalRead(jumperPin)){
        isServer = true;
        peer.setupServer();
        
        currentState = State::waitPlayer;
	}else{
        isServer = false;
        peer.setupClient();
	}
}

void handleWaitPlayer();
void handleWaitTurn();
void waitPlayerPress();
void changeTurn();

void loop() {
    switch (currentState) {
    case State::waitPlayer:
        handleWaitPlayer();
        break;
    case State::waitTurn:
        handleWaitTurn();
    default:
        break;
    }
}

void handleWaitPlayer(){
    Serial.println("Press 'start' to begin");
    
    waitPlayerPress();
    
    difficultLevel = 0;
    changeTurn();
}

void handleWaitTurn(){
    //TODO: detect if game has finished
    peer.waitTurn();
    
}

void waitPlayerPress(){
    //TODO: implement
    Serial.println("pretend player pressed...");    
}

void changeTurn(){
    ++difficultLevel;
    
    peer.sendChangeTurn(difficultLevel);
    currentState = State::waitTurn;
}
