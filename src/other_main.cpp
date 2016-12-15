///*
// * Copyright (c) 2015, Majenko Technologies
// * All rights reserved.
// * 
// * Redistribution and use in source and binary forms, with or without modification,
// * are permitted provided that the following conditions are met:
// * 
// * * Redistributions of source code must retain the above copyright notice, this
// *   list of conditions and the following disclaimer.
// * 
// * * Redistributions in binary form must reproduce the above copyright notice, this
// *   list of conditions and the following disclaimer in the documentation and/or
// *   other materials provided with the distribution.
// * 
// * * Neither the name of Majenko Technologies nor the names of its
// *   contributors may be used to endorse or promote products derived from
// *   this software without specific prior written permission.
// * 
// * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
// * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
// * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// */

///* Create a WiFi access point and provide a web server on it. */

//#include <ESP8266WiFi.h>
//#include <WiFiClient.h> 

///* Set these to your desired credentials. */
//const char *ssid = "ESPap";


//static const IPAddress server_IP(192,168,4,3);
//static const IPAddress gateway(192,168,4,9);
//static const IPAddress subnet(255,255,255,0);

//WiFiServer server(80);


//void setup() {
//	delay(5000);
//	Serial.begin(115200);
//	Serial.println();
//	Serial.print("Configuring access point...");
//	/* You can remove the password parameter if you want the AP to be open. */
	
//    WiFi.softAPConfig(server_IP, gateway, subnet);
    
//	WiFi.softAP(ssid);

//	IPAddress myIP = WiFi.softAPIP();
//	Serial.print("AP IP address: ");
//	Serial.println(myIP);
 
//	server.begin();
//	Serial.println("HTTP server started");
//}

//int lastTime = 0;
//WiFiClient client = server.available();

//void sendMessage()
//{
//    String s = 
//      "HTTP/1.1 200 OK\r\n"
//      "\r\n"
//      "Hello World!\n";
  
//    // Send the response to the client
//    client.print(s);
//    delay(1);    
//}

//void loop() {
//  // Check if a client has connected
//  if (!client || !client.connected()) {
//    client = server.available();
//    if(!client || !client.connected()){
//        return;
//    }
    
//    lastTime = millis();
//  }
  
////  // Wait until the client sends some data
////  Serial.println("new client");
////  while(!client.available()){
////    delay(1);
////  }
  
////  // Read the first line of the request
////  String req = client.readStringUntil('\r');
////  Serial.println(req);
////  client.flush();

////  // Prepare the response
////  sendMessage();
////  Serial.println("Client disonnected");


//    if(client.connected()){
//        if(millis() - lastTime > 2000){
//            sendMessage();
//            lastTime = millis();
//        }
//    }

//}
