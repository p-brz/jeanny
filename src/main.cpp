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
	Serial.begin(115200);
	setupInterface();
	
    for(uint8_t t = 5; t > 0; t--) {
        Serial.printf("[SETUP] BOOT WAIT %d...\n", t);
        Serial.flush();
        delay(1000);
    }
	
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
	
	game.begin();
}

void loop() {
//    Serial.println("- Running main loop");
    
    game.runState();
}








//#include <Arduino.h>

//#include <ESP8266WiFi.h>
//#include <ESP8266WiFiMulti.h>
//#include <WebSocketsServer.h>
//#include <WebSocketsClient.h>
//#include <Hash.h>



//WebSocketsServer webSocket_server = WebSocketsServer(81);
//bool isConnected = false;
//int pullingTime = 0;

//#define USE_SERIAL Serial



//ESP8266WiFiMulti WiFiMulti;
//WebSocketsClient webSocket_client;

//void webSocketEvent_server(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght) {

//    switch(type) {
//        case WStype_DISCONNECTED:
//            USE_SERIAL.printf("[%u] Disconnected!\n", num);
//            break;
//        case WStype_CONNECTED:
//            {
//                isConnected = true;
//                IPAddress ip = webSocket_server.remoteIP(num);
//                USE_SERIAL.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
        
//                // send message to client
//                webSocket_server.sendTXT(num, "Connected");
//            }
//            break;
//        case WStype_TEXT:
//            USE_SERIAL.printf("[%u] get Text: %s\n", num, payload);

//            // send message to client
//            // webSocket.sendTXT(num, "The cake is a lie");

//            // send data to all connected clients
//            // webSocket.broadcastTXT("message here");
//            break;
//        case WStype_BIN:
//            USE_SERIAL.printf("[%u] get binary lenght: %u\n", num, lenght);
//            hexdump(payload, lenght);

//            // send message to client
//            // webSocket.sendBIN(num, payload, lenght);
//            break;
//    }

//}

//void setup_server() {
//    delay(5000);
    
//    // USE_SERIAL.begin(921600);
//    USE_SERIAL.begin(115200);

//    //Serial.setDebugOutput(true);
//    USE_SERIAL.setDebugOutput(true);

//    USE_SERIAL.println();
//    USE_SERIAL.println();
//    USE_SERIAL.println();

//    for(uint8_t t = 4; t > 0; t--) {
//        USE_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);
//        USE_SERIAL.flush();
//        delay(1000);
//    }


//    Serial.print("Connecting...");
    
//    WiFi.begin("IMD CIVT");
//    while(WiFi.status() != WL_CONNECTED) {
//        delay(200);
//        Serial.print(".");
//    }
//    Serial.println();

//    Serial.println(WiFi.localIP());

//    webSocket_server.begin();
//    webSocket_server.onEvent(webSocketEvent_server);
//}

//void loop_server() {
//    webSocket_server.loop();
//    if(isConnected){
//      int currentTime = millis();
//      if(currentTime - pullingTime > 20000){
//        pullingTime = currentTime;
//        webSocket_server.broadcastTXT("There is no spoon");
//      }
//    }
//}


//void webSocketEvent_client(WStype_t type, uint8_t * payload, size_t lenght) {


//    switch(type) {
//        case WStype_DISCONNECTED:
//            USE_SERIAL.printf("[WSc] Disconnected!\n");
//            break;
//        case WStype_CONNECTED:
//            {
//                USE_SERIAL.printf("[WSc] Connected to url: %s\n",  payload);
        
//          // send message to server when Connected
//        webSocket_client.sendTXT("Connected");
//            }
//            break;
//        case WStype_TEXT:
//            USE_SERIAL.printf("[WSc] get text: %s\n", payload);

//      // send message to server
//      // webSocket.sendTXT("message here");
//            break;
//        case WStype_BIN:
//            USE_SERIAL.printf("[WSc] get binary lenght: %u\n", lenght);
//            hexdump(payload, lenght);

//            // send data to server
//            // webSocket.sendBIN(payload, lenght);
//            break;
//    }

//}

//void setup_client() {
//    // USE_SERIAL.begin(921600);
//    USE_SERIAL.begin(115200);

//    //Serial.setDebugOutput(true);
//    USE_SERIAL.setDebugOutput(true);

//    USE_SERIAL.println();
//    USE_SERIAL.println();
//    USE_SERIAL.println();

//      for(uint8_t t = 4; t > 0; t--) {
//          USE_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);
//          USE_SERIAL.flush();
//          delay(1000);
//      }

//    WiFiMulti.addAP("IMD CIVT");

//    //WiFi.disconnect();
//    while(WiFiMulti.run() != WL_CONNECTED) {
//        delay(100);
//    }

//    webSocket_client.begin("10.51.66.1", 81);
//    //webSocket.setAuthorization("user", "Password"); // HTTP Basic Authorization
//    webSocket_client.onEvent(webSocketEvent_client);

//}

//void loop_client() {
//    webSocket_client.loop();
//}





//const int jumperPin = 16;
//bool isServer = false;
//void setup(){
//    pinMode(jumperPin, INPUT);
//	if(digitalRead(jumperPin)){
//        isServer = true;
//        setup_server();
//	}else{
//        isServer = false;
//        setup_client();
//	}
//}

//void loop(){
//    if(isServer){
//        loop_server();
//    }
//    else{
//        loop_client();
//    }
//}











