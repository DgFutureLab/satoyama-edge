// A3GS sample sketch.8 -- httpGET

#include <SoftwareSerial.h>
#include "a3gim.h"

const char *server = "satoyamacloud.com";
const char *path = "/nodes";
int port = 80;

char res[a3gsMAX_RESULT_LENGTH+1];
int len;

void setup()
{
  Serial.begin(9600);
  delay(3000);  // Wait for Start Serial Monitor
  Serial.println("Ready.");

  Serial.print("Initializing.. ");
  if (a3gs.start() == 0 && a3gs.begin() == 0) {
    Serial.println("Succeeded.");
    Serial.print("Entering main loop.. ");
  }
  else
    Serial.println("Failed.");

//  Serial.println("Shutdown..");
//  a3gs.end();
//  a3gs.shutdown();
}

void loop()
{
  len = sizeof(res);
  if (a3gs.httpGET(server, port, path, res, len) == 0) {
    Serial.print(res);
  }
  else {
    Serial.print("Can't get HTTP response from ");
    Serial.println(server);
  }

}
