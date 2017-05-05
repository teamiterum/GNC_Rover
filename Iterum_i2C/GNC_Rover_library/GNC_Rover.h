/*
  GNC_Rover.h - Library containing all the communication
				protocols common to all modules
*/

#ifndef GNC_Rover_h
#define GNC_Rover_h

#include "Arduino.h"

class Module
{
  public:
    Module(int slaveAdress, int rw);
	
	int N_valTx;
	int N_valRx;
	int varBytesTx;
	int varBytesRx;
	
	byte* ptrTx;
	byte* ptrRx;
    
	
	void send();
    void receive();
	
  private:
    int _slaveAdress;
	int _commtype;
};

#endif