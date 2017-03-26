#include <stdio.h>
#include <cmath>

#define uintSize sizeof(unsigned int)

int main() {

	unsigned int myInt = 61615; //0000 0000  0000 0000  1111 0000  1010 1111 
	unsigned char myByte = myInt; // the char gets the 8 lsb = 175

	printf("size of integer %i\n", uintSize);
	printf("numbers: int %i char %i\n\n", myInt, myByte);

	unsigned int myIntArray[2] = { 61615 , 3855 }; //0000 0000  0000 0000  0000 1111  0000 1111
	printf("int array is %i %i\nbyte array is:\n", myIntArray[0], myIntArray[1]);
	unsigned char myByteArray[2 * uintSize];

	int i, j;

	for (i = 0; i<2; i++) {

		for (j = 0; j < uintSize; j++) {
			myByteArray[j+4*i] = myIntArray[i] >> (8 * j);
			printf(" %i", myByteArray[j + 4 * i]);
		}
		printf("\n");
	}

	printf("Reconstructed int array is:\n");
	unsigned int myIntArray2[2] = { 0,0 };
	unsigned int temp;
	
	for (i = 0; i<2; i++) {

		for (j = 0; j < uintSize; j++) {
			temp = myByteArray[j + 4 * i] << (8 * j);
			myIntArray2[i] = myIntArray2[i] | temp;
		}
		printf(" %i", myIntArray2[i]);
	}


	getchar();
}