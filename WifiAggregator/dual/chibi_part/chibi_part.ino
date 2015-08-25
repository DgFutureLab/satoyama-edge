#include <Wire.h>

/* 
  Test code for the arduino aggregator note wwhich acts as the central data collection device
  and then forwards the received data to the serial port for later upload to the Internet
  
  Written by Halfdan Rump for Future Lab. Based on code written by Christopher Wang aka Akiba.
*/

#include <chibi.h>

#define BUFSIZE 200
#define I2CADDR 9

void setup()
{
  Serial.begin(112500);
  chibiInit();
  Wire.begin(); 
  chibiSetShortAddr(1);
}

char buf[BUFSIZE];  // this is where we store the received data

void loop()
{ 
  if (chibiDataRcvd() == true){ 
    int rssi = chibiGetRSSI();
    int src_addr = chibiGetSrcAddr();
    int len = chibiGetData((unsigned char*)buf);
    Wire.beginTransmission(I2CADDR);
    for (int i=0; i< strlen(buf); i++){
      Wire.write(buf[i]);
    }
    Wire.endTransmission();
    Serial.println(buf);
  }
}

