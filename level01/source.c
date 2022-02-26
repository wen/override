#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char a_user_name[100];

int verify_user_name(void)
{
	puts("verifying username....\n");
	return strncmp(a_user_name, "dat_wil", 7);
}

int verify_user_pass(char *a_user_pass) 
{
	return strncmp(a_user_pass, "admin", 5);
}

int main(void)
{
	char a_user_pass[64] = {0};
	int x = 0;

	puts("********* ADMIN LOGIN PROMPT *********");
	printf("Enter Username: ");
	fgets(a_user_name, 0x100, stdin);

	x = verify_user_name();
	if (x != 0) {
		puts("nope, incorrect username...\n");
		return 1;
	}

	puts("Enter Password: ");
	fgets(a_user_pass, 0x64, stdin);

	x = verify_user_pass(a_user_pass);
	if (x == 0 || x != 0) {
		puts("nope, incorrect password...\n");
		return 1;
	}

	return 0;
}
