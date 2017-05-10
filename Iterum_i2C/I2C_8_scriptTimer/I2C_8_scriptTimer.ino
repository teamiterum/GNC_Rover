#include <Wire.h>
 
#define SLAVE_ADDRESS 0x04
#define valueSizeTx sizeof(long unsigned int)
#define noOfValuesTx 3
#define valueSizeRx sizeof(long unsigned int)
#define noOfValuesRx 3
#define updateRateHz  20

int updateRateus = 1000000*(1/updateRateHz);

//Create pointers to pass to the i2C request functions
byte* abpTx;
byte* abpRx;

// Create an array for the data
long unsigned int dataTx[noOfValuesTx] = {4221917887,0,0};
long unsigned int dataRx[noOfValuesRx];

int j = 0;
long unsigned int t;

void setup() {
  Serial.begin(9600);

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
  t = micros();
   
  //Change/use the values in data arrays here!

  dataTx[noOfValuesTx-1]++; 
  while( (micros()-t) < updateRateus){  
  }
}


void sendData(){
  Wire.write(abpTx,valueSizeTx*noOfValuesRx);
}

void receiveData(){
  int i;
  if(Wire.available()) {
    for(i=0;i<noOfValuesRx*valueSizeRx;i++){
      abpRx[i] = Wire.read();  
    }
    j++;
  }
}
