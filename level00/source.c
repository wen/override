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

	if (pass == 0x149c) {
		puts("\nAuthenticated!");
		system("/bin/sh");
	} else {
		puts("\nInvalid Password!");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
