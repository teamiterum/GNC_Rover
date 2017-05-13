//https://area-51.blog/2014/02/15/connecting-an-arduino-to-a-raspberry-pi-using-i2c/

#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

// The Arduino Slave i2c address
#define ADDRESS 0x04

#define uintSize sizeof(unsigned int)

// The I2C bus: This is for V2 pi's. For V1 Model B you need i2c-0
static const char *devName = "/dev/i2c-1";

int main(int argc, char** argv) {
	
	int noOfInts; //Store second argument
	
	sscanf(argv[1], "%d", &noOfInts);

	int file = open(devName, O_RDWR);
	ioctl(file, I2C_SLAVE, ADDRESS);
	
	unsigned int numbers[noOfInts]; //ints to receive, set on argc
	int noOfBytes = noOfInts * uintSize;
	
	unsigned char buf[noOfBytes];
	
    int* aip;
	aip = (int*)&buf;
	int i;
	int j;
	for(i=0; i<10; i++) {
	
		read(file, buf, noOfBytes);

		for (j = 0; j < noOfInts; j++) {
			  numbers[j] = aip[j];
			  printf("%i\n", numbers[j]);
		}
    
		usleep(10000);
	
	}
	
	close(file);
	return (EXIT_SUCCESS);
}
