#include <SoftHalfDuplexSerial.h>

const int pin_HalfDuplexSerial = 8 ; //set HalfDuplexSerial pin number
softHalfDuplexSerial hdSerial(pin_HalfDuplexSerial);

#define MOTOR_ID_1 0x01
#define MOTOR_ID_2 0x02
#define MOTOR_ID_3 0x03
#define MOTOR_ID_4 0x04
#define MOTOR_ID_5 0x05
#define MOTOR_ID_ALL 0xFE

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  hdSerial.begin(115200); // Starting half Duplex communication at 115200 bps
  hdSerial.flushRx(); // flush the Rx buffer
}

void loop() {
  // put your main code here, to run repeatedly:

  AX12_SPEED(MOTOR_ID_ALL,50); //setup speed of all motors

  AX12_POS(MOTOR_ID_1, 512);
  AX12_POS(MOTOR_ID_2, 512);
  AX12_POS(MOTOR_ID_3, 512);
  AX12_POS(MOTOR_ID_4, 512);
  AX12_POS(MOTOR_ID_5, 512);
  delay(1000);
  AX12_POS(MOTOR_ID_1, 450);
  AX12_POS(MOTOR_ID_2, 450);
  AX12_POS(MOTOR_ID_3, 450);
  AX12_POS(MOTOR_ID_4, 450);
  AX12_POS(MOTOR_ID_5, 450);
  delay(1000);
}

void AX12_POS(byte id, int data) //data=0~1023
{
  byte Head1 = 0xff;
  byte Head2 = 0xff;
  byte ID = id;
  byte Length = 3 + 2;          //Number of parameters + 2
  byte Instruction = 0x03;      //Write Instruction
  byte Parameter1 = 0x1e;       //Starting address
  byte Parameter2 = data%256;   //data low byte
  byte Parameter3 = data/256;   //data high byte
  byte Checksum = ~(ID+Length+Instruction+Parameter1+Parameter2+Parameter3);

  byte packet[] = {Head1, Head2, ID, Length, Instruction, Parameter1, Parameter2, Parameter3, Checksum};
 
  hdSerial.write(packet, (int)sizeof(packet));  //send command packet
  delay(5);
}

void AX12_SPEED(byte id, int data) //data=0~1023
{
  byte Head1 = 0xff;
  byte Head2 = 0xff;
  byte ID = id;
  byte Length = 3 + 2;          //Number of parameters + 2
  byte Instruction = 0x03;      //Write Instruction
  byte Parameter1 = 0x20;       //Starting address
  byte Parameter2 = data%256;   //data low byte
  byte Parameter3 = data/256;   //data high byte
  byte Checksum = ~(ID+Length+Instruction+Parameter1+Parameter2+Parameter3);
  
  byte packet[] = {Head1, Head2, ID, Length, Instruction, Parameter1, Parameter2, Parameter3, Checksum};

  hdSerial.write(packet, (int)sizeof(packet));  //send command packet
  delay(5);
}
