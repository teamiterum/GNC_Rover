#include <stdio.h>
int main() {
	int myArray[6] = { 5,4,3,2,1,0 };
	char myByte = (char)myArray[0];
	int sizes[2] = { sizeof(myArray[0]), sizeof(myByte) };
	printf("sizes %i %i", sizes[0], sizes[1]);
	printf("numbers %i %i", myArray[0], myByte);
	getchar();
}