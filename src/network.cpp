#include "network.h"

#include "ArduinoJson.h"

#include <string.h>


Stream &Network::stream(){
    return client;
//    return Serial;
}

void Network::setupServer(){
	Serial.println();
	Serial.print("Configuring access point...");
	
    WiFi.softAPConfig(server_IP, gateway, subnet);
    
    /* You can remove the password parameter if you want the AP to be open. */
    WiFi.softAP(ssid);

	IPAddress myIP = WiFi.softAPIP();
	Serial.print("AP IP address: ");
	Serial.println(myIP);
	
	Serial.print("Connecting to ");
    Serial.println(ssid);
    
//    WiFi.begin(ssid, password);
    
//    while (WiFi.status() != WL_CONNECTED) {
//        delay(500);
//        Serial.print(".");
//    }
//    Serial.println("");
  
	server.begin();
	Serial.println("Server started");
	
	waitClientConnect();

//    Serial.println("Not waiting client");
}

void Network::setupClient(){
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
    
    Serial.print("Connecting with server");
    
    while(!client.connect(server_IP, PORT)){
//        delay(50);
        Serial.print(".");
    }
    Serial.println();
}

bool Network::waitTurn(int & timeoutMillis){
    Serial.print("Waiting for my turn...");
    int time = millis();
    while(!stream().available()){
        if(millis() - time >= 500){
            time = millis();
            Serial.print(".");
        }
    }
    
    JBuffer jsonBuffer; 
    
    char buffer[200];
    auto readedBytes = stream().readBytesUntil('\n', buffer, 200); 
    buffer[readedBytes] = 0;

    Serial.print("received: ");
    Serial.println(buffer);
    
    JsonObject& obj = jsonBuffer.parseObject(buffer);

    if(obj.success()){
        Serial.println("Parse object Ok!");
        Serial.print("evt: ");
        const char* evt = obj["evt"];
        Serial.println(evt);
        
        if(strcmp(evt, "change_turn") == 0){
            Serial.println("Now is my turn!");
            
            timeoutMillis = obj["timeout"];
            
            Serial.print("timeout=");
            Serial.println(timeoutMillis);
            
            return true;
        }
    }
    return false;
}

void Network::sendChangeTurn(int timeoutMillis){
    JBuffer changeEvtBuffer;
    JsonObject & evt = changeEvtBuffer.createObject();
    
    evt["evt"] = "change_turn";
    evt["timeout"] = timeoutMillis;
    
    evt.printTo(stream());  
    stream().flush();
}

void Network::notifyEndGame(){
    JBuffer changeEvtBuffer;
    JsonObject & evt = changeEvtBuffer.createObject();
    
    evt["evt"] = "end_game";
    
    evt.printTo(stream()); 
    stream().flush(); 
}

void Network::waitClientConnect(){
	Serial.print("Waiting client...");
    
	//wait client
    do{
        client = server.available();
        if(!client){
//            delay(100);
//            Serial.print('.');
        }
	}while(!client); 
	
	Serial.println();
	Serial.println("Client connected!");   
}


JsonObject & Network::receiveObject(JBuffer & jsonBuffer)
{
    char buffer[200];
    auto readedBytes = stream().readBytesUntil('\n', buffer, 200); 
    buffer[readedBytes] = 0;

    Serial.print("received: ");
    Serial.println(buffer);
     
    return jsonBuffer.parseObject(buffer);
}
