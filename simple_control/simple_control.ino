#include <SoftHalfDuplexSerial.h>
#include <DynamixelAx.h>

softHalfDuplexSerial port(8); 
dxlAx dxlCom(&port);
 
void setup() {
 
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for connecting
  }
  Serial.println("Starting COM!");

  dxlCom.begin(115200); //set baudrate
}

void loop()      
{
 while(dxlCom.isBusy()); // waiting the status return delay time
 dxlCom.setGoalPosition(1, 400);
 delay(1000);
 dxlCom.setGoalPosition(1, 512);
 delay(1000);
}
