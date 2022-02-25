#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int pass;

	puts("***********************************");
	puts("* 	     -Level00 -		  *");
	puts("***********************************");
	printf("Password:");

	scanf("%d", &pass);

	if (input == 0x149c) {
		puts("\nAuthenticated!");
		system("/bin/sh");
	} else {
		printf("\nInvalid Password!\n");
		return 1;
	}

	return 0;
}
