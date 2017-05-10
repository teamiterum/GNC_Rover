#include <Wire.h>
 
#define SLAVE_ADDRESS 0x04
#define valueSizeTx sizeof(long unsigned int)
#define noOfValuesTx 2
#define valueSizeRx sizeof(long unsigned int)
#define noOfValuesRx 2

byte* abpTx;
byte* abpRx;

long unsigned int dataTx[noOfValuesTx];
long unsigned int dataRx[noOfValuesRx];

void setup() {
  // Create an array for the data
  

  // Make a pointer fo the data transfers
  abpTx = (byte*)&dataTx;
  abpRx = (byte*)&dataRx;
  
  // initialize i2c as slave
  Wire.begin(SLAVE_ADDRESS);
  
  // define callbacks for i2c communication
  Wire.onReceive(receiveData);   //These cmds act as interrupts?? 
  Wire.onRequest(sendData);  
}

void loop() {

  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);

  //Change/use the values in data arrays here!
}

void sendData(){
  Wire.write(abpTx,valueSizeTx*noOfValuesRx);
}

void receiveData(){
  abpRx = Wire.read();
}
