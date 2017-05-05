#include <Wire.h>
 
#define SLAVE_ADDRESS 0x04
int number[6] = {13,21,11,10,9,8};

void setup() {

  pinMode(13, OUTPUT); // define led toggle
  Wire.begin(SLAVE_ADDRESS);
  
  // initialize i2c as slave
  Wire.begin(SLAVE_ADDRESS);
  
  // define callbacks for i2c communication
  //Wire.onReceive(receiveData);   //These cmds act as interrupts?? 
  Wire.onRequest(sendData);
  print("size of integer %d",sizeof(number[1]));
}

void loop() {
  delay(1000);
  delay(1000);
  
}

void sendData(){
  
  Wire.write(number[0]);
  Wire.write(number[1]);

}
