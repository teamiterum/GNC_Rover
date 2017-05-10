#include <Wire.h>
 
#define SLAVE_ADDRESS 0x04
#define valueSize sizeof(long unsigned int)
#define noOfValues 1

byte* abp;
long unsigned int number[noOfValues] = {61614};

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(13, OUTPUT); // define led toggle
  
  // initialize i2c as slave
  Wire.begin(SLAVE_ADDRESS);
  
  // define callbacks for i2c communication
  //Wire.onReceive(receiveData);   //These cmds act as interrupts?? 
  Wire.onRequest(sendData);

  
  //Serial.println(sizeof(number[1]));
  
  abp = (byte*)&number;
  
  int j;
  for (j = 0; j < valueSize*noOfValues ; j++) {
    Serial.println(abp[j]); 
  }
  
}

void loop() {
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  
}

void sendData(){
  Wire.write(abp,valueSize*noOfValues);
}
