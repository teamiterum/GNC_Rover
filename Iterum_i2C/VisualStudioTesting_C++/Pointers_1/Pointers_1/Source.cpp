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

	/*for (i = 0; i < 2; i++) {
	myIntArray2[i] = aip[i];
	printf("%i\n", myByteArray[i]);
	}*/

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