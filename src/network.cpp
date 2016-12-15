#include "network.h"

#include "ArduinoJson.h"

Stream &Network::stream(){
    return client;
}

void Network::setupServer(){
	Serial.println();
	Serial.print("Configuring access point...");
	
    WiFi.softAPConfig(server_IP, gateway, subnet);
    
    /* You can remove the password parameter if you want the AP to be open. */
    WiFi.softAP(ssid, password);

	IPAddress myIP = WiFi.softAPIP();
	Serial.print("AP IP address: ");
	Serial.println(myIP);
	
	server.begin();
	Serial.println("Server started");
	
	waitClientConnect();
}

void Network::setupClient(){
    WiFi.begin(ssid, password);
    
    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.println("Connected in AP");
    
    Serial.print("Connecting with server");
    
    while(!client.connect(server_IP, PORT)){
        delay(500);
        Serial.print(".");
    }
    Serial.println();
}

void Network::waitTurn(){
    Serial.print("Waiting for my turn...");
    int time = millis();
    while(!stream().available()){
        if(millis() - time >= 500){
            time = millis();
            Serial.print(".");
        }
    }
    
    StaticJsonBuffer<200> jsonBuffer; 
    JsonObject& obj = receiveObject(jsonBuffer);

    if(obj.success() && obj["evt"] == "change_turn"){
        Serial.println("Now is my turn!");
    }
}

void Network::sendChangeTurn(int difficultLevel){
    StaticJsonBuffer<200> changeEvtBuffer;
    JsonObject & evt = changeEvtBuffer.createObject();
    
    evt["evt"] = "change_turn";
    evt["level"] = difficultLevel;
    
    evt.printTo(stream());  
}

void Network::waitClientConnect(){
	Serial.print("Waiting client...");
    
	//wait client
    do{
        client = server.available();
        if(!client){
            delay(500);
            Serial.print('.');
        }
	}while(!client); 
	
	Serial.println();
	Serial.println("Client connected!");   
}


JsonObject & Network::receiveObject(StaticJsonBuffer<200> & jsonBuffer)
{
    char buffer[200];
    auto readedBytes = stream().readBytesUntil('\n', buffer, 200);  
    JsonObject & obj = jsonBuffer.parseObject(buffer);
    
    return obj;
}
