/* Create a WiFi access point and provide a web server on it. */

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

#define PORT 8266

IPAddress server_IP(192,168,4,3);
IPAddress gateway(192,168,4,9);
IPAddress subnet(255,255,255,0);

int jumperPin = 14;
const int buttonsPins[] = {14, 12};
const int ledPins[] = {5, 4};

/* Set these to your desired credentials. */
const char *ssid = "ESPap";
const char *password = "thereisnospoon";

WiFiServer server(PORT);
WiFiClient client;
bool isServer = false;

enum class State{
    waitPlayer,
    waitTurn,
    waitKey
};
State currentState;

void setupInterface(){
    for(int i=0;i < 3; ++i){
        pinMode(buttonsPins[i], INPUT);
        pinMode(ledPins[i], OUTPUT);
    }
}

void setupServer(){
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
	
	currentState = State::waitPlayer;
}

void setupClient(){
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

void setup() {
	delay(5000);
	Serial.begin(115200);
	
	setupInterface();
	
	pinMode(jumperPin, INPUT);
	if(digitalRead(jumperPin)){
        isServer = true;
        setupServer();
	}else{
        isServer = false;
        setupClient();
	}
}

void loop() {
    if(isServer){
    }else{
        // handle client loop
    }
}

//void loop(){
//    for(int i=0;i < 2; ++i){
//        auto pin = buttonsPins[i];
//        digitalWrite(ledPins[i], digitalRead(pin));
//    }
//}
