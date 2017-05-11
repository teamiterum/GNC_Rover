#include <Wire.h>
#include <TimerOne.h>
 
#define SLAVE_ADDRESS 0x04
#define valueSizeTx sizeof(long unsigned int)
#define noOfValuesTx 1

int analogPin = A3;
byte* abpTx;


// Create an array for the data
int res = 0;
unsigned int res2 = 666;

void setup() {
  Serial.begin(9600);

  //Timer1.initialize(5000); 
  //Timer1.attachInterrupt(takeReading);

  abpTx = (byte*)&res2;
  Wire.begin(SLAVE_ADDRESS);
  Wire.onRequest(sendData);  
}

void loop() {
  
  //delay(5);
  /*digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);*/
  //Serial.println(res);
  
    
}


void sendData(){
  Wire.write(abpTx,2);
}

void takeReading()
{
  
  res = analogRead(analogPin);
  //res2++;
  //Serial.println(abpTx[0]);  
}

