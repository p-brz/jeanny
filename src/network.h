#ifndef NETWORK_H
#define NETWORK_H

#include <ESP8266WiFi.h>
#include <Hash.h>
#include <WebSocketsServer.h>
#include <WebSocketsClient.h>
#include "ArduinoJson.h"
#include <functional>

#define PORT 8266
#define PORT_WEBSOCKET 81

static const char * serverIPStr = "192.168.4.3";
static const IPAddress server_IP(192,168,4,3);
static const IPAddress gateway(192,168,4,9);
static const IPAddress subnet(255,255,255,0);

/* Set these to your desired credentials. */
//static constexpr const char *ssid = "ESPap";
static constexpr const char *ssid = "ESP____wifi";
//static constexpr const char *password = "thereisnospoon";

using JBuffer = StaticJsonBuffer<200>;

using Object = JsonObject;
using OnEventHandler = std::function<void(const char *, Object &)>;

class Network{
public:

    WiFiServer server{PORT};
    WiFiClient client;
//    WebSocketsServer webSocket{PORT_WEBSOCKET};
//    WebSocketsClient webSocketClient;

    bool isConnected = false;
    bool isServer = false;
    int lastTimeRequest = 0;

    OnEventHandler onEventHandler;

    Stream & stream();

    void setupServer();
    void setupClient();

    void update();
    
    void sendPing();

    void clientConnect();
    void receiveEvent();
    
    void setOnEvent(const OnEventHandler & handler);
protected:    
    void onEvent(const char * evtName, JsonObject & obj);
public:
    bool waitTurn(int & timeoutMillis);
    void sendChangeTurn(int timeoutMillis);
    void notifyEndGame();
    
//    void write(const String & str);
    void serverUpdate();
    
    void clientUpdate();
    
    void checkConnectionWithClient();
    
protected:
    void waitClientConnect();
};

#endif // NETWORK_H
