
#include <chibi.h>
//#include <chibi.h>
#include <config.h>
#include <Adafruit_CC3000.h>
#include <ccspi.h>
#include <SPI.h>
#include <string.h>
#include "utility/debug.h"
#include <config.h>
#include <utilsawesome.h>
// These are the interrupt and control pins
#define ADAFRUIT_CC3000_IRQ   3  // MUST be an interrupt pin!
// These can be any two pins
#define ADAFRUIT_CC3000_VBAT  5
#define ADAFRUIT_CC3000_CS    10
// Use hardware SPI for the remaining pins
// On an UNO, SCK = 13, MISO = 12, and MOSI = 11
Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT,
                                         SPI_CLOCK_DIVIDER); // you can change this clock speed

//#define WLAN_SSID       "HWD15_F49FF3ED0D6D"           // cannot be longer than 32 characters!
//#define WLAN_PASS       "10ii3ybg21f8317"
//#define WLAN_SSID       "FutureLab"           // cannot be longer than 32 characters!
//#define WLAN_PASS       "tacobeya11"
#define WLAN_SSID       "AirPort25512"           // cannot be longer than 32 characters!
#define WLAN_PASS       "1739818891249"
// Security can be WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA or WLAN_SEC_WPA2
#define WLAN_SECURITY   WLAN_SEC_WPA2

#define IDLE_TIMEOUT_MS  3000      // Amount of time to wait (in milliseconds) with no data 
                                   // received before closing the connection.  If you know the server
                                   // you're accessing is quick to respond, you can reduce this value.

// What page to grab!
//#define WEBSITE      "google.com"
//#define WEBPAGE      "/"

#define WEBSITE      "satoyamacloud.com"
#define WEBPAGE      "/reading"



/**************************************************************************/
/*!
    @brief  Sets up the HW and the CC3000 module (called automatically
            on startup)
*/
/**************************************************************************/

uint32_t ip;
int counter = 0;

void setup(void)
{
  Serial.begin(115200);
  chibiInit();
  chibiSetShortAddr(AGGREGATOR_SHORT_ADDRESS);
  wifi_connect();
    // this is where we store the received data
}

byte buf[TX_LENGTH];
void loop()
{ 
  Serial.println();
  Serial.print("Counter: ");
  Serial.println(counter);
  counter += 1;
  memset(buf, 0, TX_LENGTH);
  Serial.print(F("Free RAM after buf: ")); Serial.println(getFreeRam(), DEC);
  for(int i = 0; i<5; i++){
    Reading battery_voltage = {"vbat", 2, millis()};
    add_to_tx_buf((char*) buf, &battery_voltage);

    delay(1000);
  }
  Serial.println((char *)buf);
  Serial.print(F("Free RAM after readings: ")); Serial.println(getFreeRam(), DEC);
  
  Serial.print(F("Free RAM before send_data: ")); Serial.println(getFreeRam(), DEC);
  send_data((char*) buf);
  
  
//  Serial.print(F("Free RAM before free buf: ")); Serial.println(getFreeRam(), DEC);
//  if (chibiDataRcvd() == true){ 
//    Serial.println(F("chibiDataRcvd"));
//    int rssi = chibiGetRSSI();
//    int src_addr = chibiGetSrcAddr();
//    int len = chibiGetData(buf);
//    if (len == 0) {
//      return;
//    } else{
//      Serial.println(F("printBufferToSerial"));
//      printBufferToSerial(src_addr, buf);
//    }
//  }
//  free(buf);
//  Serial.print(F("Free RAM after free buf: ")); Serial.println(getFreeRam(), DEC);
}


void printBufferToSerial(int src_addr, byte *buf){
  Serial.print("^");
  Serial.print(src_addr);
  Serial.print("@");
  Serial.println((char*)buf);
}



void send_data(char data[]){
  Serial.println("Just in send_data");
  char data_len_str[15];
  Serial.println("A");
  sprintf(data_len_str, "%d", strlen(data) + 5);
  Serial.print("Content length: ");
  Serial.println(data_len_str);
  Adafruit_CC3000_Client www = cc3000.connectTCP(ip, 80);
  Serial.print(F("Free RAM before send: ")); Serial.println(getFreeRam(), DEC);

  if (www.connected()) {
      Serial.println(F("1"));
//      char buf = "POST /readings HTTP/1.1\r\nHost: satoyamacloud.com\r\nContent-Length: 29\r\nAccept: */*\r\nConnection: keep-alive\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\ndata=1,2.5,2015-8-10 16:46:13";
//      www.fastrprint(F("POST /reading HTTP/1.1\r\nHost: satoyamacloud.com\r\nContent-Length: 21\r\nAccept: */*\r\nConnection: keep-alive\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\nsensor_id=2&value=28"));
//        www.fastrprint(F("POST /readings HTTP/1.1\r\nHost: satoyamacloud.com\r\nContent-Length: 29\r\nAccept: */*\r\nConnection: keep-alive\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\ndata=1,2.5,2015-8-10 16:46:13"));
//        char *buf = "POST /readings HTTP/1.1\r\nHost: satoyamacloud.com\r\nContent-Length: 29\r\nAccept: */*\r\nConnection: keep-alive\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\ndata=1,2.5,2015-8-10 16:46:13";
//        www.print(F("POST /readings HTTP/1.1\r\nHost: satoyamacloud.com\r\nContent-Length: 29\r\nAccept: */*\r\nConnection: keep-alive\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\ndata=1,2.5,2015-8-10 16:46:13"));
//        int len = strlen(buf);
//        for(int i = 0; i < len; i++){
//          Serial.print(buf[i]);
//          www.print(buf[i]);
//        }
//        www.println(F("POST /readings HTTP/1.1\r\nHost: satoyamacloud.com\r\nContent-Length: 29\r\nAccept: */*\r\nConnection: keep-alive\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\ndata=1,2.5,2015-8-10 16:46:13"));
      www.fastrprint(F("POST /readings HTTP/1.1\r\nHost: satoyamacloud.com\r\nContent-Length: 29"));
      delay(100);
//      Serial.println(F("2"));
//      www.fastrprint(data_len_str);
//      Serial.println(F("3"));
////      1,2.33,2015-8-6;2,5.66,2015-8-7 22:00:01
      www.fastrprint(F("\r\nAccept: */*\r\nConnection: keep-alive\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\ndata="));
      delay(100);
      char * um = "1,2.5,2015-8-10 16:46:13";
      www.fastrprint(um);
      delay(100);
//      Serial.println(F("4"));
//      www.fastrprint(data);
//      Serial.println(F("5"));
////      root.printTo(www);
//  delay(1)
      www.println();
      Serial.print(F("Free RAM after send: ")); Serial.println(getFreeRam(), DEC);
  } else {
    Serial.println(F("Connection failed"));
    www.close();
    wifi_disconnect();
    delay(5000);
    wifi_connect();
    return;
  }
  free(data_len_str);
  Serial.println(F("-------------------------------------"));
  
  /* Read data until either the connection is closed, or the idle timeout is reached. */ 
  unsigned long lastRead = millis();
  while (www.connected() && (millis() - lastRead < IDLE_TIMEOUT_MS)) {
    while (www.available()) {
      char c = www.read();
      Serial.print(c);
      lastRead = millis();
    }
  }
  www.close();
  Serial.println(F("-------------------------------------"));
  Serial.print(F("Free RAM after close: ")); Serial.println(getFreeRam(), DEC);
}





void wifi_disconnect(){
  /* You need to make sure to clean up after yourself or the CC3000 can freak out */
  /* the next time your try to connect ... */
  Serial.println(F("\n\nDisconnecting"));
  cc3000.disconnect();
  

}

void wifi_connect(){
  Serial.println(F("Hello, CC3000!\n")); 

  Serial.print("Free RAM: "); Serial.println(getFreeRam(), DEC);
  
  /* Initialise the module */
  Serial.println(F("\nInitializing..."));
  if (!cc3000.begin())
  {
    Serial.println(F("Couldn't begin()! Check your wiring?"));
    while(1);
  }
  
  // Optional SSID scan
  // listSSIDResults();
  
  Serial.print(F("\nAttempting to connect to ")); Serial.println(WLAN_SSID);
  if (!cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
    Serial.println(F("Failed!"));
    while(1);
  }
   
  Serial.println(F("Connected!"));
  
  /* Wait for DHCP to complete */
  Serial.println(F("Request DHCP"));
  while (!cc3000.checkDHCP())
  {
    delay(100); // ToDo: Insert a DHCP timeout!
  }  

  /* Display the IP address DNS, Gateway, etc. */  
  while (! displayConnectionDetails()) {
    delay(1000);
  }

//  ip = 2160562973;
  ip = 0;
  // Try looking up the website's IP address
  Serial.print(WEBSITE); Serial.print(F(" -> "));
  while (ip == 0) {
    if (! cc3000.getHostByName(WEBSITE, &ip)) {
      Serial.println(F("Couldn't resolve!"));
    }
    delay(500);
  }
  cc3000.printIPdotsRev(ip);
  
  Serial.println("Wifi connection established. ");
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
    Serial.println(F("SSID scan failed!"));
    return;
  }

  Serial.print(F("Networks found: ")); Serial.println(index);
  Serial.println(F("================================================"));

  while (index) {
    index--;

    valid = cc3000.getNextSSID(&rssi, &sec, ssidname);
    
    Serial.print(F("SSID Name    : ")); Serial.print(ssidname);
    Serial.println();
    Serial.print(F("RSSI         : "));
    Serial.println(rssi);
    Serial.print(F("Security Mode: "));
    Serial.println(sec);
    Serial.println();
  }
  Serial.println(F("================================================"));

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
    Serial.println(F("Unable to retrieve the IP Address!\r\n"));
    return false;
  }
  else
  {
    Serial.print(F("\nIP Addr: ")); cc3000.printIPdotsRev(ipAddress);
    Serial.print(F("\nNetmask: ")); cc3000.printIPdotsRev(netmask);
    Serial.print(F("\nGateway: ")); cc3000.printIPdotsRev(gateway);
    Serial.print(F("\nDHCPsrv: ")); cc3000.printIPdotsRev(dhcpserv);
    Serial.print(F("\nDNSserv: ")); cc3000.printIPdotsRev(dnsserv);
    Serial.println();
    return true;
  }
}
