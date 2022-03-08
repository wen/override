#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LEN 41

int main(int argc, char *argv[])
{
	char dotpass[LEN] = {0};
	char user[100] = {0};
	char pass[100] = {0};

	FILE *fp = fopen("/home/users/level03/.pass", "r");
	if (!fp) {
		fprintf(stderr, "ERROR: failed to open password file\n");
		exit(EXIT_FAILURE);
	}
	if (fread(dotpass, 1, LEN, fp) != LEN) {
		fprintf(stderr, "ERROR: failed to read password file\n");
		exit(EXIT_FAILURE);
	}
	dotpass[strcspn(dotpass, "\n")] = '\0';
	fclose(fp);

	puts("===== [ Secure Access System v1.0 ] =====");
	puts("/***************************************\\");
	puts("| You must login to access this system. |");
	puts("\\**************************************/");
	printf("--[ Username: ");
	fgets(user, 100, stdin);
	user[strcspn(user, "\n")] = '\0';    
	printf("--[ Password: ");
	fgets(pass, 100, stdin);
	pass[strcspn(pass, "\n")] = '\0';
	puts("*****************************************");

	if (!strncmp(dotpass, pass, LEN)) {
		printf("Greetings, %s!\n", user);
		system("/bin/sh");
	} else {
		printf(user);
		puts(" does not have access!");
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}
