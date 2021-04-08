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


void loop() {
  port.flushRx(); // flush the Rx buffer
  
  while(dxlCom.isBusy()); // waiting the status return delay time
  byte id = 0x01;
  dxlCom.readPresentPosition(id);
          
  while(!dxlCom.dxlDataReady());        // waiting the answer of servo

  auto error = dxlCom.readDxlError();
  if(error!=DXL_ERR_SUCCESS) // readDxlResult should always be called before readDxlData
    Serial.print("read error : ");
    
  unsigned short readValue = dxlCom.readDxlResult();
  
  Serial.println(readValue);

  delay(1000);
}
