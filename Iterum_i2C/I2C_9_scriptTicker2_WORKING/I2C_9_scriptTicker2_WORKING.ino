#include <Wire.h>
#include <TimerOne.h>
 
#define SLAVE_ADDRESS 0x04
#define valueSizeTx sizeof(long unsigned int)
#define noOfValuesTx 1
#define valueSizeRx sizeof(long unsigned int)
#define noOfValuesRx 3
#define updateRateHz  200

int updateRatems = 1000*(1/updateRateHz);

//Create pointers to pass to the i2C request functions
byte* abpTx;
byte* abpRx;

// Create an array for the data
long unsigned int dataTx[noOfValuesTx];
//long unsigned int dataRx[noOfValuesRx];

// Create an array where to transfer data to send
long unsigned int storeTx[noOfValuesTx];
long unsigned int storeRx[noOfValuesRx];

int k = 0;
int j = 0;

void setup() {
  Serial.begin(9600);
  
  Timer1.initialize(5000); 
  Timer1.attachInterrupt(takeReading);
  // Make a pointer fo the data transfers
  abpTx = (byte*)&storeTx;
  abpRx = (byte*)&storeRx;
  
  // initialize i2c as slave
  Wire.begin(SLAVE_ADDRESS);
  
  // define callbacks for i2c communication
  Wire.onReceive(receiveData);   //These cmds act as interrupts?? 
  Wire.onRequest(sendData);  
}

void loop() {
  
  delay(500);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  
  int i;
  for (i = 0; i < noOfValuesRx ; i++) {
    Serial.print(".");
    Serial.println(storeRx[i]);
  }
  /*for (i = 0; i < valueSizeRx*noOfValuesRx ; i++) {
    Serial.println(abpRx[i]);
  }*/
  
  //Serial.println();
  
  Serial.println(k);
  Serial.println(j);
  
  Serial.println();
  
  //Change/use the values in data arrays here!

  //dataTx[noOfValuesTx-2]++;
  
}


void sendData(){
  Wire.write(abpTx,valueSizeTx*noOfValuesRx);
}

void receiveData(){
  int i;
  while(Wire.available()) {
    for(i=0;i<noOfValuesRx*valueSizeRx;i++){
      abpRx[i] = Wire.read();  
    }
  j++;
  }
}

void takeReading()
{
  dataTx[noOfValuesTx-1]++;
  int i;
  for(i = 0; i < noOfValuesTx; i++){
    storeTx[i] = dataTx[i];
  }
  
  k++;
}
