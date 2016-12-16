#include "network.h"

#include "ArduinoJson.h"

#include <string.h>

#define PING_TIME 10000

Stream &Network::stream(){
    return client;
//    return Serial;
}

void Network::setupServer(){
    this->isServer = true;
    
	Serial.println();
	Serial.print("Configuring access point...");
	
    WiFi.softAPConfig(server_IP, gateway, subnet);
    
    /* You can remove the password parameter if you want the AP to be open. */
    WiFi.softAP(ssid);

	IPAddress myIP = WiFi.softAPIP();
	
	Serial.print("Setup WiFI AP:");
    Serial.println(ssid);
    
	Serial.print("AP IP address: ");
	Serial.println(myIP);
  
	server.begin();
    
	Serial.println("Server started");
}

void Network::setupClient(){
    this->isServer = false;
    
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid);
    
    Serial.print("Connecting to ");
    Serial.print(ssid);
    
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.println("Connected in AP");
}

void Network::update(){
    if(isServer){
        serverUpdate();
    }
    else {
        clientUpdate();
    }
}

void Network::sendPing(){
    // Send the response to the client
    client.println("{\"evt\":\"ping\"}");
    delay(1);    
}

void Network::serverUpdate(){
    checkConnectionWithClient();
    
    if(client.connected()){
        receiveEvent();
    
        if(millis() - lastTimeRequest > PING_TIME){
            sendPing();
            lastTimeRequest = millis();
        }
    }    
}

void Network::clientUpdate(){
    if(!client.connected()){
        clientConnect();
    }
    
    if(client.connected()){
        receiveEvent();            
    }    
}

void Network::checkConnectionWithClient(){
    if (!client || !client.connected()) {
        client = server.available();
        if(client && client.connected()){
            lastTimeRequest = millis();
        }
    }    
}

void Network::clientConnect(){
    Serial.print("connecting to server");
    
    if (!client.connect(server_IP, PORT)) {
        Serial.println("connection failed");
        return;
    }
}

void Network::receiveEvent(){
    if(client.available()){
        String line = client.readStringUntil('\n');
        
        Serial.print("received: ");
        Serial.println(line);

        JBuffer jsonBuffer; 
        
        JsonObject& obj = jsonBuffer.parseObject(line);
    
        if(obj.success()){
            Serial.println("Parse object Ok!");
            
            if(obj.containsKey("evt")){
                onEvent(obj["evt"], obj);
            }
        }     
        
        lastTimeRequest = millis();   
    }
}

void Network::setOnEvent(const OnEventHandler & handler){
    this->onEventHandler = handler;
}

void Network::onEvent(const char * evtName, JsonObject & obj){
    Serial.print("evt: ");
    obj.printTo(Serial);
    Serial.println();
    
    if(onEventHandler){
        onEventHandler(evtName, obj);
    }
}

void Network::sendChangeTurn(int timeoutMillis){
    Serial.println("send change turn!");
    
    JBuffer changeEvtBuffer;
    JsonObject & evt = changeEvtBuffer.createObject();
    
    evt["evt"] = "change_turn";
    evt["timeout"] = timeoutMillis;
    
    sendEvent(evt);
}

void Network::sendEvent(JsonObject& evt)
{
    evt.printTo(stream()); 
    stream().println();
    stream().flush();   
    
    Serial.print("sent evt:");
    Serial.println((const char *)evt["evt"]);
//    evt.printTo(Serial);
//    Serial.println();
}

void Network::notifyEndGame(){
    JBuffer changeEvtBuffer;
    JsonObject & evt = changeEvtBuffer.createObject();
    
    evt["evt"] = "end_game";
    sendEvent(evt); 
}
