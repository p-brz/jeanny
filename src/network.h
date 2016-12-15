#ifndef NETWORK_H
#define NETWORK_H

#include <ESP8266WiFi.h>

#include "ArduinoJson.h"

#define PORT 8266

static const IPAddress server_IP(192,168,4,3);
static const IPAddress gateway(192,168,4,9);
static const IPAddress subnet(255,255,255,0);

/* Set these to your desired credentials. */
//static constexpr const char *ssid = "ESPap";
static constexpr const char *ssid = "ESP____wifi";
//static constexpr const char *password = "thereisnospoon";

using JBuffer = StaticJsonBuffer<200>;

class Network{
public:

    WiFiServer server{PORT};
    WiFiClient client;

    Stream & stream();

    void setupServer();
    void setupClient();

public:
    bool waitTurn(int & timeoutMillis);
    void sendChangeTurn(int timeoutMillis);
    void notifyEndGame();
    
    JsonObject & receiveObject(JBuffer & jsonBuffer);
    
protected:
    void waitClientConnect();
};

#endif // NETWORK_H
