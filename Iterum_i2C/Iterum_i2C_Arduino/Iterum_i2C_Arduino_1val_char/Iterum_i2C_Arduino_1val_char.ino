#include <Wire.h>
 
#define SLAVE_ADDRESS 0x04
char number = 12;

void setup() {

  pinMode(13, OUTPUT); // define led toggle haha
  Wire.begin(SLAVE_ADDRESS);
  
  // initialize i2c as slave
  Wire.begin(SLAVE_ADDRESS);
  
  // define callbacks for i2c communication
  //Wire.onReceive(receiveData);   //These cmds act as interrupts?? 
  Wire.onRequest(sendData);
}

void loop() {
  delay(1000);
  delay(1000);
  
}

void sendData(){
 
  Wire.write(number);
}
