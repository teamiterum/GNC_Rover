#include <Wire.h>
#include <Arduino.h>

 class Module
{
  public:
  Module(int slaveAdress, int rw);
 
  int N_valTx;
  int N_valRx;
  int varBytesTx;
  int varBytesRx;
  
  byte* ptrTx;
  byte* ptrRx;
  
  private:
    int _slaveAdress;
  int _commtype;
};

Module::Module(int slaveAdress, int rw)
{
  _slaveAdress = slaveAdress;
  _commtype = rw;
  
  
  Wire.begin(_slaveAdress);
  
}


/*void comm(Module module) {
  //if rw==0...
  Wire.onRequest(Wire.write(module.ptrTx,module.N_valTx*module.varBytesTx)); //????????
}*/

#define SLAVE_ADDRESS 0x04
#define valueSize sizeof(long unsigned int)
#define noOfValues 3

Module Motor(SLAVE_ADDRESS,1);
long unsigned int number[noOfValues] = {4221917887,4578946572,4221917888}; 


void setup() {
  
  Motor.ptrTx = (byte*)&number;
  Motor.N_valTx = noOfValues;
  Motor.varBytesTx = valueSize;
  comms();
  
}

void loop() {
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);  
}

void sendData(){
  Wire.write(Motor.ptrTx,valueSize*noOfValues);
}

void comms(){
  Wire.onRequest(sendData);
}


