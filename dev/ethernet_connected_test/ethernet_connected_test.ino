/*
  Repeating Web client
 
 This sketch connects to a a web server and makes a request
 using a Wiznet Ethernet shield. You can use the Arduino Ethernet shield, or
 the Adafruit Ethernet shield, either one will work, as long as it's got
 a Wiznet Ethernet module on board.
 
 This example uses DNS, by assigning the Ethernet client with a MAC address,
 IP address, and DNS address.
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 
 created 19 Apr 2012
 by Tom Igoe
 
 http://arduino.cc/en/Tutorial/WebClientRepeating
 This code is in the public domain.
 
 */
#include <chibi.h>
#define NODE_ID 1
#define BUFSIZE 300
char buf[BUFSIZE];

#define TMPSIZE 150
char tmp[TMPSIZE]; 

#include <SPI.h>
#include <Ethernet.h>

// assign a MAC address for the ethernet controller.
// fill in your address here:

#define PORT 80
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
// fill in an available IP address on your network here,
// for manual configuration:
IPAddress ip(192,168,0,177);

// fill in your Domain Name Server address here:


// initialize the library instance:
EthernetClient client;

char server[] = "satoyamacloud.com";

unsigned long lastConnectionTime = 0;          // last time you connected to the server, in milliseconds
boolean lastConnected = false;                 // state of the connection last time through the main loop
const unsigned long postingInterval = 2*1000;  // delay between updates, in milliseconds

boolean con;

void setup() {
  Serial.begin(115200);
  // start serial port:
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
//  chibiInit();
//  chibiSetShortAddr(NODE_ID);
  
  Serial.println("Attempting to connect Ethernet using DHCP");

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  Serial.print("Ethernet initialized with local IP: ");
  Serial.println(Ethernet.localIP());
  Serial.println("Connecting");
  con = client.connect(server, 80);
}

boolean chibi_on = false;


/*************************************
    loop
***************************************/

void loop() {
  Serial.println(client.connected());
  delay(1000);
  if(!client.connected()){
    Serial.println("Connecting");
    client.connect(server, 80);
  }

}

