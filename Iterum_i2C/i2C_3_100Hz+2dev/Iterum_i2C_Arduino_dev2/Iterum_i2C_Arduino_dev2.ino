#include <Wire.h>
 
#define SLAVE_ADDRESS 0x05
#define valueSize sizeof(long unsigned int)
#define noOfValues 2

byte* abp;

long unsigned int number[noOfValues] = {100 , 5};
//Serial.println(sizeof(number[1]));

void setup() {

//For debugging
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  
// initialize i2c
  Wire.begin(SLAVE_ADDRESS); //declare as slave
  Wire.onRequest(sendData); //function when data requesteded from master
  
  abp = (byte*)&number; //sending the number arrays byte by byte

//Verify that the pointers split the numbers correctly in bytes
  int j;
  for (j = 0; j < valueSize*noOfValues ; j++) {
    Serial.println(abp[j]); 
  }
  
}

void loop() {
  delay(10000);  
}

void sendData(){
  Wire.write(abp,valueSize*noOfValues); //send the whole number array
  
//for debugging purposes     
  number[0] = number[0] - 1;
}
