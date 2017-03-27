#include <Wire.h>
 
#define SLAVE_ADDRESS 0x04
#define uintSize sizeof(unsigned int)


char* abp;

void setup() {

  pinMode(13, OUTPUT); // define led toggle
  
  // initialize i2c as slave
  Wire.begin(SLAVE_ADDRESS);
  
  // define callbacks for i2c communication
  //Wire.onReceive(receiveData);   //These cmds act as interrupts?? 
  Wire.onRequest(sendData);

  unsigned int number[2] = {61615 , 3855};
  abp = (char*)&number;
  
}

void loop() {
  delay(1000);
  delay(1000);
  
}

void sendData(){
  int j;
  for (j = 0; j < X; j++) {
  Wire.write(abp[j]);    
  }    
}
