#include <stdio.h>
#include <cmath>

#define uintSize sizeof(unsigned int)

int main() {

	unsigned int myIntArray[2] = { 61615 , 3855 }; //0000 0000  0000 0000  0000 1111  0000 1111
	printf("int array is %i %i\n", myIntArray[0], myIntArray[1]);
	unsigned char myByteArray[2 * uintSize];

	char* abp;
	abp = (char*)&myIntArray;

	int i;
	int j;
	for (i = 0; i < (2 * uintSize); i++) {
		myByteArray[i] = abp[i];
		printf("%i\n", myByteArray[i]);
	}

	unsigned int myIntArray2[2] = { 0,0 };


	for (i = 0; i < 2; i++) {
		myIntArray2[i] = abp[i];
		printf("%i\n", myIntArray[i]);
	}


	getchar();
}