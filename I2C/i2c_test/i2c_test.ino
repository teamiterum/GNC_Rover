///*  
//
// *   
// */
//#include <Wire.h>
//int ADXLAddress = 0x53; // Device address in which is also included the 8th bit for selecting the mode, read in this case.
//#define X_Axis_Register_DATAX0 0x32 // Hexadecima address for the DATAX0 internal register.
//#define X_Axis_Register_DATAX1 0x33 // Hexadecima address for the DATAX1 internal register.
//#define Power_Register 0x2D // Power Control Register
//
//void setup() {
//  pinMode(LED_BUILTIN, OUTPUT);
//  Wire.begin(); // Initiate the Wire library
//  Serial.begin(9600);
//  delay(100);
//  // Enable measurement
//  Wire.beginTransmission(ADXLAddress);
//  Wire.write(Power_Register);
//  // Bit D3 High for measuring enable (0000 1000)
//  Wire.write(8);  
//  Wire.endTransmission();
//}
//void loop() {
//  Wire.beginTransmission(ADXLAddress); // Begin transmission to the Sensor 
//  //Ask the particular registers for dat
// 
//
//
//}

// --------------------------------------
// i2c_scanner
//
// Version 1
//    This program (or code that looks like it)
//    can be found in many places.
//    For example on the Arduino.cc forum.
//    The original author is not know.
// Version 2, Juni 2012, Using Arduino 1.0.1
//     Adapted to be as simple as possible by Arduino.cc user Krodal
// Version 3, Feb 26  2013
//    V3 by louarnold
// Version 4, March 3, 2013, Using Arduino 1.0.3
//    by Arduino.cc user Krodal.
//    Changes by louarnold removed.
//    Scanning addresses changed from 0...127 to 1...119,
//    according to the i2c scanner by Nick Gammon
//    http://www.gammon.com.au/forum/?id=10896
// Version 5, March 28, 2013
//    As version 4, but address scans now to 127.
//    A sensor seems to use address 120.
// Version 6, November 27, 2015.
//    Added waiting for the Leonardo serial communication.
//
//
// This sketch tests the standard 7-bit addresses
// Devices with higher bit address might not be seen properly.
//
 
#include <Wire.h>
 
 
void setup()
{
  Wire.begin();
 
  Serial.begin(9600);
  while (!Serial);             // Leonardo: wait for serial monitor
  Serial.println("\nI2C Scanner");
}
 
 
void loop()
{
  byte error, address;
  int nDevices;
 
  Serial.println("Scanning...");
 
  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
 
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");
 
      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknown error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
 
  delay(5000);           // wait 5 seconds for next scan
}
