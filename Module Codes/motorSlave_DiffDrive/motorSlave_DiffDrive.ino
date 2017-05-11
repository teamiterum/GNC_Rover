#include <Wire.h>
 
#define SLAVE_ADDRESS 0x04
#define X  unsigned int     // Type of Variable for Data (ie byte etc) 

#define valueSizeTx sizeof(X)
#define noOfValuesTx 1
#define valueSizeRx sizeof(X)
#define noOfValuesRx 3     // Number of Motors in this case 


//Create pointers to pass to the i2C request functions
byte* abpTx;
byte* abpRx;

// Create an array where to transfer data to send
X storeTx[noOfValuesTx];
X storeRx[noOfValuesRx];

//User Definitions and Variables
byte mask = 3; 
byte control = 0;
unsigned int pwmValue = 0; //Concatenate pwmValue1 and pwmValue2  
X motor_array[noOfValuesRx][2];


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
  int i;
  delay(500);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);

  for(i=0;i<noOfValuesRx;i++){
      instructionDecode(i);
      Serial.println(motor_array[i][0]);
      Serial.println(motor_array[i][1]);
    }
  // Change/use the values in data arrays here!
  
}

int instructionDecode(int motor){
  
  control = abpRx[motor*2] & mask; 
  motor_array[motor][0]=control;
  pwmValue = storeRx[motor];
  pwmValue = pwmValue >> 2; 
  motor_array[motor][1]=pwmValue;
  
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
