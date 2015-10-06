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

/*
  Sensor definitions and imports
*/
#include <utilsawesome.h>
#include "dht11.h"

#define TEMPERATURE_SENSOR_ID 8
#define HUMIDITY_SENSOR_ID 9
#define SONAR_SENSOR_ID 7
#define VBAT_SENSOR_ID 6
#define NODE_ID 3

dht11 DHT;
#define DHT11_PIN 4

/*
  Edge stuff
*/
#define BUFSIZE 300
char buf[BUFSIZE];
char tmp[100];
char data_length[10];
char http_args[] = "format=compact&data=";


/*
  Ethernet stuff
*/


#include <SPI.h>
#include <Ethernet.h>

// assign a MAC address for the ethernet controller.
// fill in your address here:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
// fill in an available IP address on your network here,
// for manual configuration:
IPAddress ip(192,168,1,15);

// fill in your Domain Name Server address here:
// initialize the library instance:
EthernetClient client;
char server[] = "satoyamacloud.com";
unsigned long lastConnectionTime = 0;          // last time you connected to the server, in milliseconds
boolean lastConnected = false;                 // state of the connection last time through the main loop
const unsigned long postingInterval = 2*1000;  // delay between updates, in milliseconds


/*
  Timer stuff
*/
#include "TimerOne.h"
void check_connection(){
  Serial.print("Conneciton: ");
  Serial.print(client.connected());
  Serial.print(" ,status: ");
  Serial.println(client.status(), HEX);
}


void setup() {
  Serial.begin(115200);
  // start serial port:
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.println("Attempting to connect Ethernet using DHCP");

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  Serial.println("Connection established!");
  Timer1.initialize(5000000);
  Timer1.attachInterrupt(check_connection);
}



void read_and_post(){
 
}





void loop() {
  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:
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
  if(!client.connected() && (millis() - lastConnectionTime > postingInterval)) {
    memset(buf, 0, BUFSIZE);
    read_dht((char*)buf);
    Serial.println((char*) buf);
    Serial.println("Sending HTTP request");
    post_data(buf);
    Serial.println("P14");
//    httpRequest();
  }
  // store the state of the connection for next time through
  // the loop:
  lastConnected = client.connected();
}





// this method makes a HTTP connection to the server:
void httpRequest() {
  // if there's a successful connection:
  if (client.connect(server, 80)) {
    Serial.println("connecting...");
    // send the HTTP PUT request:
    client.println("GET / HTTP/1.1");
    client.println("Host: www.arduino.cc");
    client.println("User-Agent: arduino-ethernet");
    client.println("Connection: keep-alive");
    client.println();

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






void post_data(char* buf) {
  // if there's a successful connection:
  
  Serial.println("P-1");
  if (client.connect(server, 80)) {
    memset(data_length, 0, 10);
    sprintf(data_length, "%d", strlen(buf) + strlen(http_args));
    
    Serial.println("P0");
    // send the HTTP PUT request:
    client.println("POST /readings HTTP/1.1");
    Serial.println("P1");
    client.println("Host: satoyamacloud.com");
    Serial.println("P2");
    client.println("User-Agent: arduino-ethernet-home");
    Serial.println("P3");
    client.println("Connection: keep-alive");
    Serial.println("P4");
    client.println("Content-Type: application/x-www-form-urlencoded");
    Serial.println("P5");
    client.print("Content-length: ");
    Serial.println("P6");
    client.println(data_length);
    client.print("\r\n");
    Serial.println("P7");
    client.print(http_args);
    Serial.println("P8");
    client.println(buf);
    Serial.println("P9");
    // note the time that the connection was made:
    lastConnectionTime = millis();
    Serial.println("P10");
    Serial.println("P11");
  } 
  else {
    // if you couldn't make a connection:
    Serial.println("connection failed, disconnecting");
    client.stop();
    Serial.println("P12");
  }
  Serial.println("P13");
  
}












void read_dht(char* buf){
  int chk;
//  Serial.print("DHT11, \t");
  chk = DHT.read(DHT11_PIN);    // READ DATA
  switch (chk){
    case DHTLIB_OK:  
//                Serial.print("OK,\t"); 
                break;
    case DHTLIB_ERROR_CHECKSUM: 
//                Serial.print("Checksum error,\t"); 
                break;
    case DHTLIB_ERROR_TIMEOUT: 
//                Serial.print("Time out error,\t"); 
                break;
    default: 
//                Serial.print("Unknown error,\t"); 
                break;
  }
 // DISPLAT DATA
  Reading temp = {NODE_ID, TEMPERATURE_SENSOR_ID, DHT.temperature, millis()};
  append_reading((char*) buf, &temp);

  Reading humidity = {NODE_ID, HUMIDITY_SENSOR_ID, DHT.humidity, millis()};
  append_reading((char*) buf, &humidity);

}



