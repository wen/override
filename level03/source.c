#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 17

void decrypt(unsigned int key)
{
	char str[LEN] = "Q}|u`sfg~sf{}|a3";

	for (int i = 0; i != LEN - 1; ++i)
		str[i] ^= key;
	
	if (!strcmp(str, "Congratulations!"))
		system("/bin/sh");
	else
		puts("\nInvalid Password");
}

void test(unsigned int pass, unsigned int key)
{
	key -= pass;

	switch (key) {
	case 0x1:
	case 0x2:
	case 0x3:
	case 0x4:
	case 0x5:
	case 0x6:
	case 0x7:
	case 0x8:
	case 0x9:
	case 0x10:
	case 0x11:
	case 0x12:
	case 0x13:
	case 0x14:
	case 0x15:
		decrypt(key);
		break;
	default:
		decrypt(rand());
	}
}

int main(void)
{
	int pass;

	srand(time(NULL));
	puts("***********************************");
	puts("*		level03		**");
	puts("***********************************");
	printf("Password:");

	scanf("%d", &pass);
	test(pass, 0x1337d00d);

	return EXIT_SUCCESS;
}
