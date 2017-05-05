#include <Wire.h>
 
#define SLAVE_ADDRESS 0x04
#define valueSize sizeof(long unsigned int)
#define noOfValues 3

byte* abp;
long unsigned int number[noOfValues] = {4221917887,4578946572,4221917888};
byte temp[noOfValues*valueSize];

void setup() {
  Serial.begin(9600);
  //Serial.println(valueSize);
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(13, OUTPUT); // define led toggle
  
  // initialize i2c as slave
  Wire.begin(SLAVE_ADDRESS);
  
  // define callbacks for i2c communication
  //Wire.onReceive(receiveData);   //These cmds act as interrupts?? 
  Wire.onRequest(sendData);

  
  //Serial.println(sizeof(number[1]));
  
  abp = (byte*)&number;
  
  int i;
  int j;
  for (i = 0; i < valueSize*noOfValues ; i++) {
    Serial.println(abp[i]); 
  }
  
  
  for(i = 0; i < noOfValues; i++) {  
    for(j = valueSize; j > 0; j--){
       temp[(i*valueSize)+(4-j)] = abp[(i*valueSize)+(j-1)];          
    }
  }
  
  Serial.println("\n"); 
  
  for (i = 0; i < valueSize*noOfValues ; i++) {
    Serial.println(temp[i]); 
  }
  
}

void loop() {
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  
}

void sendData(){
  Wire.write(temp,valueSize*noOfValues);
}
