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

//*** Performing Checks and starting communication ***\\

	// Check that at least two arguments have been input
	if (argc == 1) {
		printf("Supply one or more commands to send to the Arduino\n");
		exit(1);
	}

	// Check if the second argument is a decimal


	if (0 == sscanf(argv[1], "%d", &noOfInts)) {
		fprintf(stderr, "Invalid parameter %d \"%s\"\n", noOfInts, argv[1]);
        exit(1);
	}

	// Start communication with device
	printf("I2C: Connecting\n");
	int file = open(devName, O_RDWR);

	// Check if the communication started correctly
	if ( file < 0) {
		fprintf(stderr, "I2C: Failed to access %d\n", devName);
		exit(1);
	}

	printf("I2C: acquiring buss to 0x%x\n", ADDRESS);

	if (ioctl(file, I2C_SLAVE, ADDRESS) < 0) {
		fprintf(stderr, "I2C: Failed to acquire bus access/talk to slave 0x%x\n", ADDRESS);
		exit(1);
	}

//***Performing Checks and starting communication***\\
	
	unsigned int numbers[noOfInts]; //ints to receive, set on argc
	int noOfBytes = noOfInts * uintSize;
	
	// if the argument is not zero, read data
	if (noOfInts != 0) {

        unsigned char buf[noOfBytes];
		
        read(file, buf, noOfBytes);
		
		// Checking what was received
		printf("buffer bytes:\n");
		int i;
		for (i = 0; i < noOfBytes; i++) {
			printf("%i\n", buf[i]);
		}
		
		// Transfering data to integers
        int* aip;
	aip = (int*)&buf;
	int j;
	for (j = 0; j < noOfInts; j++) {
		numbers[j] = aip[j];
		printf("%i\n", numbers[j]);
	}		
		

	}
	else {
          printf("Invalid number, %d \n",noOfInts);
	}
    // Now wait else you could crash the arduino by sending requests too fast
    //usleep(10000);

	close(file);
	return (EXIT_SUCCESS);
}
