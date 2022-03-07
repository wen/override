#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char a_user_name[0x64]; // 0804a040 g O .bss	00000064	a_user_name

int verify_user_name(void)
{
	puts("verifying username....\n");
	return strncmp(a_user_name, "dat_wil", 7);
}

int verify_user_pass(char *pass) 
{
	return strncmp(pass, "admin", 5);
}

int main(void)
{
	char pass[0x40] = {0};
	int ret;

	puts("********* ADMIN LOGIN PROMPT *********");
	printf("Enter Username: ");
	fgets(a_user_name, 0x100, stdin);
	// 0x08048519 <+73>:	mov    DWORD PTR [esp+0x4],0x100
	ret = verify_user_name();
	if (ret != 0) {
		puts("nope, incorrect username...\n");
		return EXIT_FAILURE;
	}

	puts("Enter Password: ");
	fgets(pass, 0x64, stdin);
	// 0x08048565 <+149>:	mov    DWORD PTR [esp+0x4],0x64
	ret = verify_user_pass(pass);
	if (ret == 0 || ret != 0) {
		puts("nope, incorrect password...\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
