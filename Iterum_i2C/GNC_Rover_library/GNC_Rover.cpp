#include "Arduino.h"
#include "Wire.h"
#include "GNC_Rover.h"

Module::Module(int slaveAdress, int rw)
{
	_slaveAdress = slaveAdress;
	_commtype = rw;
	
	
	Wire.begin(SLAVE_ADDRESS);
	Wire.onRequest(sending); //????????
	Wire.onReceive(receive); //????????
}

void Module::sending()
{
	Wire.write(ptrTx,N_valTx*varBytesTx);
}

void Morse::receive()
{
	Wire.read();
}