#include "Arduino.h"
#include "GNC_Rover.h"

Module::Module(int slaveAdress, int rw)
{
	Wire.begin(SLAVE_ADDRESS);
	Wire.onRequest(send); //????????
	Wire.onReceive(receive); //????????
}

void Module::send()
{
	Wire.write(ptrTx,N_valTx*varBytesTx);
}

void Morse::receive()
{
	Wire.read(ptrRx,N_valRx*varBytesRx);
}