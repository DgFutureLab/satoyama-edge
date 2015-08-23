#include <config.h>
#include <Adafruit_CC3000.h>
#include <ccspi.h>
#include <SPI.h>
#include <string.h>
#include "utility/debug.h"
#include <chibi.h>

// These are the interrupt and control pins
#define ADAFRUIT_CC3000_IRQ   3  // MUST be an interrupt pin!
// These can be any two pins
#define ADAFRUIT_CC3000_VBAT  5
#define ADAFRUIT_CC3000_CS    10
// Use hardware SPI for the remaining pins
// On an UNO, SCK = 13, MISO = 12, and MOSI = 11
Adafruit_CC3000 cc3000= Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT,
                                         SPI_CLOCK_DIVIDER); // you can change this clock speed

#define WLAN_SSID       "AirPort25512"           // cannot be longer than 32 characters!
#define WLAN_PASS       "1739818891249"
// Security can be WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA or WLAN_SEC_WPA2
#define WLAN_SECURITY   WLAN_SEC_WPA2

#define IDLE_TIMEOUT_MS  3000      // Amount of time to wait (in milliseconds) with no data 
                                   // received before closing the connection.  If you know the server
                                   // you're accessing is quick to respond, you can reduce this value.

#define WEBSITE      "satoyamacloud.com"
#define WEBPAGE      "/readings"

#define NODE_ID 1

#define BUFSIZE 100
#define WIFI_TX_CHUNK_SIZE 50
#define REPLY_SIZE 50


/**************************************************************************/
/*!
    @brief  Sets up the HW and the CC3000 module (called automatically
            on startup)
*/
/**************************************************************************/

uint32_t ip;
char buf[BUFSIZE];
char tmp[100];
char reply[REPLY_SIZE];
char content_length[3];
char http_args[] = "format=compact&data=";
char tx_slice_buf[WIFI_TX_CHUNK_SIZE + 1];

void setup(void)
{
  memset(buf, 0, BUFSIZE);
  chibiInit();
  chibiSetShortAddr(NODE_ID);
  Serial.println(printf("Short address: %d", chibiGetShortAddr()));
  Serial.begin(115200);
  Serial.println("Connecting");
  wifi_connect();
  Serial.print(F("Free RAM after setup: ")); Serial.println(getFreeRam(), DEC);
}

void loop()
{ 
//  strcat(buf, "sssssssssssssssssssssssssssssssssssssss");
  chibi_recv(buf);
  if(strlen(buf) > 10){
    Serial.print("buffer: ");
    Serial.println(buf);
    Serial.println("Sending data");
    send_data(buf);
    memset(buf, 0, BUFSIZE);
  }
  
  delay(100);
}


void chibi_recv(char *buf){
  memset(tmp, 0, 100);
  if (chibiDataRcvd() == true){ 
    int rssi = chibiGetRSSI();
    int src_addr = chibiGetSrcAddr();
    int len = chibiGetData((byte*)tmp);
    strcat(buf, tmp);
  }
}



void send_data(char* buf){
  Serial.println(getFreeRam(), DEC);
  Adafruit_CC3000_Client www = cc3000.connectTCP(ip, 80);  
  Serial.println(getFreeRam(), DEC);
  Serial.println(buf);
  memset(content_length, 0, 3);
  sprintf(content_length, "%d", strlen(buf) + strlen(http_args));
  if (www.connected()) {
    Serial.println("Connected.");
      www.fastrprint(F("POST /readings HTTP/1.1\r\nHost: satoyamacloud.com\r\nContent-Length: "));
      www.fastrprint(content_length);
      delay(50);
      Serial.print("-");
      www.fastrprint(F("\r\nAccept: */*\r\nConnection: keep-alive\r\n"));
      delay(50);
      Serial.print("-");
      www.fastrprint(F("Content-Type: application/x-www-form-urlencoded\r\n\r\n"));
      www.fastrprint(http_args);
      delay(100);
      Serial.print("-");
      
      int chunks = floor(strlen(buf) / WIFI_TX_CHUNK_SIZE);
      int remaining = strlen(buf) - chunks * WIFI_TX_CHUNK_SIZE;
      for(int chunk = 0; chunk < chunks; chunk++){
        memset(tx_slice_buf, 0, WIFI_TX_CHUNK_SIZE);
        memcpy(tx_slice_buf, &buf[chunk * WIFI_TX_CHUNK_SIZE], WIFI_TX_CHUNK_SIZE);
        tx_slice_buf[WIFI_TX_CHUNK_SIZE] = '\0';
        Serial.println(tx_slice_buf);
      }
      memset(tx_slice_buf, 0, WIFI_TX_CHUNK_SIZE);
      memcpy(tx_slice_buf, &buf[chunks * WIFI_TX_CHUNK_SIZE], remaining);
      tx_slice_buf[WIFI_TX_CHUNK_SIZE] = '\0';
      Serial.println(tx_slice_buf);
      
//      for(int j=0; j<2; j++){
//        www.fastrprint("1111111111111111111111111111111111111111");
//        Serial.print(".");
//        delay(100);
//     }
  } else {
    Serial.println("Not connected");
    www.close();
    return;
  }
 
  /* Read data until either the connection is closed, or the idle timeout is reached. */ 
  memset(reply, 0, REPLY_SIZE);
  unsigned long lastRead = millis();
  while (www.connected() && (millis() - lastRead < IDLE_TIMEOUT_MS) && (strlen(reply)< REPLY_SIZE)) {
    while (www.available()) {
      char c = www.read();
//      int hum = 3;
//      strcat(reply, c);
      Serial.print(c);
      lastRead = millis();
    }
  }
  www.close();
  Serial.println("www closed");
}





void wifi_disconnect(){
  /* You need to make sure to clean up after yourself or the CC3000 can freak out */
  /* the next time your try to connect ... */
//  Serial.println(F("\n\nDisconnecting"));
  cc3000.disconnect();
  

}

void wifi_connect(){
  Serial.println("Connecting");
  if (!cc3000.begin())
  {
    Serial.println(F("Couldn't begin()! Check your wiring?"));
    while(1);
  }
  if (!cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
    Serial.println(F("Failed!"));
    while(1);
  }
   
  while (!cc3000.checkDHCP())
  {
    delay(100); // ToDo: Insert a DHCP timeout!
  }  

  /* Display the IP address DNS, Gateway, etc. */  
  while (! displayConnectionDetails()) {
    delay(1000);
  }

  ip = 0;
  // Try looking up the website's IP address
//  Serial.print(WEBSITE); Serial.print(F(" -> "));
  while (ip == 0) {
    if (! cc3000.getHostByName(WEBSITE, &ip)) {
//      Serial.println(F("Couldn't resolve!"));
    }
    delay(500);
  }
  cc3000.printIPdotsRev(ip);
}



/**************************************************************************/
/*!
    @brief  Begins an SSID scan and prints out all the visible networks
*/
/**************************************************************************/

void listSSIDResults(void)
{
  uint32_t index;
  uint8_t valid, rssi, sec;
  char ssidname[33]; 

  if (!cc3000.startSSIDscan(&index)) {
    return;
  }

  while (index) {
    index--;

    valid = cc3000.getNextSSID(&rssi, &sec, ssidname);
 }

  cc3000.stopSSIDscan();
}

/**************************************************************************/
/*!
    @brief  Tries to read the IP address and other connection details
*/
/**************************************************************************/
bool displayConnectionDetails(void)
{
  uint32_t ipAddress, netmask, gateway, dhcpserv, dnsserv;
  
  if(!cc3000.getIPAddress(&ipAddress, &netmask, &gateway, &dhcpserv, &dnsserv))
  {
    return false;
  }
  else
  {
    return true;
  }
}
