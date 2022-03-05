#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clear_stdin(void)
{
	char c;

	while (1) {
		c = getchar();
		if (c == '\n' || c == EOF)
			break;
	}
}

unsigned int get_unum(void)
{
	unsigned int buf = 0;

	fflush(stdout);
	scanf("%u", &buf);
	clear_stdin();

	return buf;
}

int store_number(unsigned int *data)
{
	unsigned int n;
	unsigned int index;

	printf(" Number: ");
	n = get_unum();
	printf(" Index: ");
	index = get_unum();

	if (index % 3 == 0 || (n >> 24) == 0xb7) {
		puts(" *** ERROR! ***");
		puts("   This index is reserved for wil!");
		puts(" *** ERROR! ***");

		return 1;
	}

	data[index] = n;

	return 0;
}


int read_number(unsigned int *data)
{
	unsigned int index = 0;

	printf(" Index: ");
	index = get_unum();
	printf(" Number at data[%u] is %u\n", index, data[index]);

	return 0;
}

int main(int argc, char *argv[])
{
	for (; *argv; ++argv)
		memset(*argv, 0, strlen(*argv));

	puts("----------------------------------------------------\n"\
		 "  Welcome to wil's crappy number storage service!   \n"\
		 "----------------------------------------------------\n"\
		 " Commands:                                          \n"\
		 "    store - store a number into the data storage    \n"\
		 "    read  - read a number from the data storage     \n"\
		 "    quit  - exit the program                        \n"\
		 "----------------------------------------------------\n"\
		 "   wil has reserved some storage :>                 \n"\
		 "----------------------------------------------------\n");

	int ret;
	char cmd[20] = {0};
	unsigned int data[100] = {0};

    while(1) {
		printf("Input command: ");
		ret = 1;

		fgets(cmd, sizeof(cmd), stdin);
		cmd[strlen(cmd) - 1] = '\0';

		if (!strncmp(cmd, "store", 5))
			ret = store_number(data);
		else if (!strncmp(cmd, "read", 4))
			ret = read_number(data);
		else if (!strncmp(cmd, "quit", 4))
			break;

		if (ret)
			printf(" Failed to do %s command\n", cmd);
		else
			printf(" Completed %s command successfully\n", cmd);

		memset(cmd, 0, sizeof(cmd));
    }

	return EXIT_SUCCESS;
}
