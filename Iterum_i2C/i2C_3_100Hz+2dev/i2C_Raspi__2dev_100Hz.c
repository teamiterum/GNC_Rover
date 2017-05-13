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
#define ADDRESS1 0x04
#define ADDRESS2 0x05

#define values1Size sizeof(unsigned int)
#define noOfvalues1 2

#define values2Size sizeof(unsigned int)
#define noOfvalues2 2

// The I2C bus: This is for V2 pi's. For V1 Model B you need i2c-0
static const char *devName = "/dev/i2c-1";

int main(int argc, char** argv) {

// Initialising communications
	int file1 = open(devName, O_RDWR);
	ioctl(file1, I2C_SLAVE, ADDRESS1);
	
	int file2 = open(devName, O_RDWR );
	ioctl(file2, I2C_SLAVE, ADDRESS2);

	
	unsigned int values1[noOfvalues1]; //ints to receive, set on argc
	int noOfBytes1 = values1Size * noOfvalues1;
	unsigned char buf1[noOfBytes1];
    int* aip1;
	aip1 = (int*)&buf1;
	
	unsigned int values2[noOfvalues2]; //ints to receive, set on argc
	int noOfBytes2 = values2Size * noOfvalues2;
	unsigned char buf2[noOfBytes2];
    int* aip2;
	aip2 = (int*)&buf2;

	int arg;
	sscanf(argv[1], "%d", &arg);
	int i;
	int j;
	
	for(i=0; i<arg; i++) {
	
		read(file1, buf1, noOfBytes1);
		read(file2, buf2, noOfBytes2);

		for (j = 0; j < noOfvalues1; j++) {
			  values1[j] = aip1[j];
			  printf("%i\n", values1[j]);
		}
		printf("\n");
		
		for (j = 0; j < noOfvalues2; j++) {
			  values2[j] = aip2[j];
			  printf("%i\n", values2[j]);
		}
    
		usleep(100);
		printf("\n");
		printf("\n");	
	}
	
	close(file1);
	close(file2);
	return (EXIT_SUCCESS);
}
