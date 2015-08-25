
#include <Wire.h>
#define I2CADDR 9
#define BUFSIZE 200

char buf[BUFSIZE];

void setup() {
  // Define the LED pin as Output
  // Start the I2C Bus as Slave on address 9
  Serial.begin(115200);
  Wire.begin(I2CADDR); 
  // Attach a function to trigger when something is received.
  Wire.onReceive(receiveEvent);
}

void receiveEvent(int bytes) {
  memset(buf, 0, BUFSIZE);
  for(int i=0; i< bytes; i++){
    char x = Wire.read();
    char tmp[2] = {x, '\0'};
    strcat(buf, tmp);    // read one character from the I2C
  }
  Serial.println(buf);
}

void loop() {
  //If value received is 0 blink LED for 200 ms

}
