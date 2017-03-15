#include <Wire.h>
 
#define SLAVE_ADDRESS 0x04
int number = 0;
int state = 0;
 
double temp;
 
void setup() {
 pinMode(13, OUTPUT);
 
 // initialize i2c as slave
 Wire.begin(SLAVE_ADDRESS);
 
 // define callbacks for i2c communication
 Wire.onReceive(receiveData);   //These cmds act as interrupts?? 
 Wire.onRequest(sendData);
}
 

void loop() {
  delay(5000);
  temp = toggle();
}
 


// callback for received data
void receiveData(int byteCount){
 
 while(Wire.available()) {
  number = Wire.read();
  if (number == 1){
   if (state == 0){
    number = 666;
   }
  } if(number==2) {
   number = (int)temp;
  }
 }
}
 
// callback for sending data
void sendData(){
 Wire.write(number);
}

double toggle(void){
  double i;
   if (state == 0){
    digitalWrite(13, HIGH); // set the LED on
    i = 42;
    state = 1;
   } else{
    digitalWrite(13, LOW); // set the LED off
    i = 50;
    state = 0;
   }
  return i;
}
 

