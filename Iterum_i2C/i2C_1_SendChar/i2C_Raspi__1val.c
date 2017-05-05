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
 
// The I2C bus: This is for V2 pi's. For V1 Model B you need i2c-0
static const char *devName = "/dev/i2c-1";

int main(int argc, char** argv) {

  int arg; //Store second argument

//*** Performing Checks and starting communication ***\\

  // Check that at least two arguments have been input
  if (argc == 1) {
    printf("Supply one or more commands to send to the Arduino\n");
    exit(1);
  }
  
  // Check if the second argument is a decimal
  int val; //Use it future code for number of values to read
  
  if (0 == sscanf(argv[1], "%d", &arg)) {
	fprintf(stderr, "Invalid parameter %d \"%s\"\n", arg, argv[1]);
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

  // if the ardument was one, read data
  if (arg == 1) {

	char buf[1] = {0};
	read(file, buf, 1);
	if (buf[0] != 0) {
	  int number = (int) buf[0];
	  printf("Received %d\n", number);
	} else
	  printf("Didn't receive anything. buffer is %d \n",buf[0]);
  } 
  else {
	  printf("Invalid number, %d \n",arg);
  }
    // Now wait else you could crash the arduino by sending requests too fast
    //usleep(10000);

  close(file);
  return (EXIT_SUCCESS);
}