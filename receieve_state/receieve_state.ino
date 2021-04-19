#include <SoftHalfDuplexSerial.h>
#include <TimerOne.h>

typedef struct Motor_state
{
  int Model_Number;
  int Firmware_Version;
  int ID;
  int Baud_Rate;
  int Return_Delay_Time;
  int CW_Angle_Limit;
  int CCW_Angle_Limit;
  int Temperature_Limit;
  int Min_Voltage_Limit;
  int Max_Voltage_Limit;
  int Max_Torque;
  int Status_Return_Level;
  int Alarm_LED;
  int Shutdown;
  int Torque_Enable;
  int LED;
  int CW_Compliance_Margin;
  int CCW_Compliance_Margin;
  int CW_Compliance_Slope;
  int CCW_Compliance_Slope;
  int Goal_Position;
  int Moving_Speed;
  int Torque_Limit;
  int Present_Position;
  int Present_Speed;
  int Present_Load;
  int Present_Voltage;
  int Present_Temperature;
  int Registered;
  int Moving;
  int Lock;
  int Punch;
};

Motor_state M1;

const int pin_HalfDuplexSerial = 10 ; //set HalfDuplexSerial pin number
softHalfDuplexSerial hdSerial(pin_HalfDuplexSerial);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  hdSerial.begin(115200); // Starting half Duplex communication at 115200 bps
  hdSerial.flushRx(); // flush the Rx buffer

  Timer1.initialize(1000000);
  Timer1.attachInterrupt(timer_returnState);
}

void loop() {
  // put your main code here, to run repeatedly:
  AX12_POS(1, 500);
  delay(1000);
  AX12_POS(1, 600);
  delay(1000);

  
}

void timer_returnState()
{
  hdSerial.flushRx(); // flush the Rx buffer
  AX12_allState(0x01);
  Save_state(M1);

  Serial.println(M1.Present_Position);
}

void Save_state(Motor_state& M)
{
  int nByte = 0;
  byte myBuffer[51];
  while(hdSerial.available())
  {
    myBuffer[nByte] = hdSerial.read();  // read from half duplex serial
    nByte += 1; // add one byte
    Serial.println( myBuffer[nByte-1]);
  }
  M.Model_Number = myBuffer[1]*256 + myBuffer[0];
  M.Firmware_Version;
  M.ID;
  M.Baud_Rate;
  M.Return_Delay_Time;
  M.CW_Angle_Limit;
  M.CCW_Angle_Limit;
  M.Temperature_Limit;
  M.Min_Voltage_Limit;
  M.Max_Voltage_Limit;
  M.Max_Torque;
  M.Status_Return_Level;
  M.Alarm_LED;
  M.Shutdown;
  M.Torque_Enable;
  M.LED;
  M.CW_Compliance_Margin;
  M.CCW_Compliance_Margin;
  M.CW_Compliance_Slope;
  M.CCW_Compliance_Slope;
  M.Goal_Position;
  M.Moving_Speed;
  M.Torque_Limit;
  M.Present_Position = myBuffer[37]<<8 + myBuffer[36];
  M.Present_Speed;
  M.Present_Load;
  M.Present_Voltage;
  M.Present_Temperature;
  M.Registered;
  M.Moving;
  M.Lock;
  M.Punch;
  
}

void AX12_allState(byte id) //data=0~1023
{
  byte Head1 = 0xff;
  byte Head2 = 0xff;
  byte ID = id;
  byte Instruction = 0x02;
  byte Length = 2 + 2;          //Number of parameters + 2
  byte Parameter1 = 36;       //Starting address
  byte Parameter2 = 2;   //data low byte
  byte Checksum = ~(ID+Length+Instruction+Parameter1+Parameter2);
  
  byte packet[] = {Head1, Head2, ID, Length, Instruction, Parameter1, Parameter2, Checksum};

  hdSerial.write(packet, sizeof(packet));
  delay(5);
}

void AX12_POS(byte id, int data) //data=0~1023
{
  byte Head1 = 0xff;
  byte Head2 = 0xff;
  byte ID = id;
  byte Instruction = 0x03;
  byte Length = 3 + 2;          //Number of parameters + 2
  byte Parameter1 = 0x1e;       //Starting address
  byte Parameter2 = data%256;   //data low byte
  byte Parameter3 = data/256;   //data high byte
  byte Checksum = ~(ID+Length+Instruction+Parameter1+Parameter2+Parameter3);
  
  byte packet[] = {Head1, Head2, ID, Length, Instruction, Parameter1, Parameter2, Parameter3, Checksum};

  hdSerial.write(packet, sizeof(packet));
  delay(5);
}

void AX12_SPEED(byte id, int data) //data=0~1023
{
  byte Head1 = 0xff;
  byte Head2 = 0xff;
  byte ID = id;
  byte Instruction = 0x03;
  byte Length = 3 + 2;          //Number of parameters + 2
  byte Parameter1 = 0x20;       //Starting address
  byte Parameter2 = data%256;   //data low byte
  byte Parameter3 = data/256;   //data high byte
  byte Checksum = ~(ID+Length+Instruction+Parameter1+Parameter2+Parameter3);
  
  byte packet[] = {Head1, Head2, ID, Length, Instruction, Parameter1, Parameter2, Parameter3, Checksum};

  hdSerial.write(packet, sizeof(packet));
  delay(5);
}
