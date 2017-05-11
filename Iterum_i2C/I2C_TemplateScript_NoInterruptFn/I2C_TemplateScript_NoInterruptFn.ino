#include <Wire.h>
 
#define SLAVE_ADDRESS 0x04
#define X long unsigned int

#define valueSizeTx sizeof(X)
#define noOfValuesTx 1
#define valueSizeRx sizeof(X)
#define noOfValuesRx 3


//Create pointers to pass to the i2C request functions
byte* abpTx;
byte* abpRx;

// Create an array where to transfer data to send
X storeTx[noOfValuesTx];
X storeRx[noOfValuesRx];

void setup() {
  Serial.begin(9600);
  
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
  
  /*int i;
  for (i = 0; i < noOfValuesRx ; i++) {
    Serial.print(".");
    Serial.println(storeRx[i]);
  }*/
  /*for (i = 0; i < valueSizeRx*noOfValuesRx ; i++) {
    Serial.println(abpRx[i]);
  }*/
  
  // Change/use the values in data arrays here!
  
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
  }
}
