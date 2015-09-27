/*
  Web client
 
 This sketch connects to a website (http://www.google.com)
 using an Arduino Wiznet Ethernet shield. 
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 
 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe, based on work by Adrian McEwen
 
 */

#include <SPI.h>
#include <Ethernet.h>
#include <chibi.h>
#define BUFSIZE 400

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char server[] = "satoyamacloud.com";    // name address for Google (using DNS)

unsigned long lastConnectionTime = 0;          // last time you connected to the server, in milliseconds
boolean lastConnected = false;                 // state of the connection last time through the main loop
const unsigned long postingInterval = 12*1000;  // delay between updates, in milliseconds

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192,168,0,177);

// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

#define NODE_ID 1

char buf[BUFSIZE];
char tmp[100];
char data_length[3];
char http_args[] = "format=compact&data=";

void setup() {
 // Open serial communications and wait for port to open:
  memset(buf, 0, BUFSIZE);
  chibiInit();
  chibiSetShortAddr(NODE_ID);
  
  Serial.begin(115200);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
}

void loop() {
 
  if (chibiDataRcvd() == true){ 
//    memset(buf, 0, BUFSIZE);
    Serial.println("DATA RECEIVED");
    int rssi = chibiGetRSSI();
    int src_addr = chibiGetSrcAddr();
    memset(tmp, 0, 100);
    int len = chibiGetData((byte*)tmp);
    strcat(buf, tmp);
    Serial.println(buf);
    Serial.println(strlen(buf));
  } 
  
  if(strlen(buf) > BUFSIZE - 100){
    Serial.print("Posting data: ");
    Serial.println(buf);
    post_data(buf);
    memset(buf, 0, BUFSIZE);
  }
  
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // if there's no net connection, but there was one last time
  // through the loop, then stop the client:
  if (!client.connected() && lastConnected) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
  }

  // if you're not connected, and ten seconds have passed since
  // your last connection, then connect again and send data:
//  if(!client.connected() && (millis() - lastConnectionTime > postingInterval)) {
//    httpRequest();
//  }
  // store the state of the connection for next time through
  // the loop:
  lastConnected = client.connected();
}

void post_data(char* buf) {
  // if there's a successful connection:
  
  
  if (client.connect(server, 80)) {
    memset(data_length, 0, 3);
    sprintf(data_length, "%d", strlen(buf) + strlen(http_args));
    
    Serial.println("connecting...");
    // send the HTTP PUT request:
    client.println("POST /readings HTTP/1.1");
    client.println("Host: satoyamacloud.com");
    client.println("User-Agent: arduino-ethernet-home");
    client.println("Connection: close");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-length: ");
    client.println(data_length);
    client.print("\r\n");
    client.print(http_args);
    client.println(buf);

    // note the time that the connection was made:
    lastConnectionTime = millis();
  } 
  else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
    Serial.println("disconnecting.");
    client.stop();
  }
}





