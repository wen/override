#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#ifndef __APPLE__
#include <sys/ptrace.h>
#endif

#define LEN 32

int auth(char *username, unsigned int serial)
{
	username[strcspn(username, "\n")] = '\0';
	int len = strnlen(username, LEN);

	if (len < 6)
		return 1;

#ifndef __APPLE__
	if (ptrace(PTRACE_TRACEME, 0, 1, 0) == -1) {
		puts("\x1b[32m" ".---------------------------.");
		puts("\x1b[31m"   "| !! TAMPERING DETECTED !!  |");
		puts("\x1b[32m" "'---------------------------'");

		return 1;
	}
#endif

	unsigned int hash = (username[3] ^ 0x1337) + 0x5eeded;
	for (int i = 0; i < len; ++i) {
		if (username[i] < 32 || username[i] > 127)
			return 1;
		hash += (username[i] ^ hash) % 0x539;
	}

#ifdef DEBUG
	printf("username: %s\nserial: %u\n", username, hash);
#endif

	return serial == hash ? 0 : 1;
}

int main(int argc, char *argv[])
{
	char username[LEN];
	unsigned int serial;

	puts("***********************************");
	puts("*		level06		  *");
	puts("***********************************");
	printf("-> Enter Login: ");

	fgets(username, LEN, stdin);

	puts("***********************************");
	puts("***** NEW ACCOUNT DETECTED ********");
	puts("***********************************");
	printf("-> Enter Serial: ");

	scanf("%u", &serial);

	if (!auth(username, serial)) {
		printf("Authenticated!\n");
		system("/bin/sh");
		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;
}
