#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct packet
{
	char msg[140];
	char username[40];
	int len;
};

void secret_backdoor(void)
{
	char buf[128];

	fgets(buf, 128, stdin);
	system(buf);
}

void set_username(struct packet *p)
{
	char buf[128] = {0};

	puts(">: Enter your username");
	printf(">>: ");
	fgets(buf, 128, stdin);
	for (int i = 0; i <= 40 && buf[i]; ++i)
		p->username[i] = buf[i];
	printf(">: Welcome, %s", p->username);
}

void set_msg(struct packet *p)
{
	char buf[1024] = {0};

	puts(">: Msg @Unix-Dude\n");
	printf(">>: ");
	fgets(buf, 1024, stdin);
	strncpy(p->msg, buf, p->len);
}

void handle_msg(void)
{
	struct packet p;

	memset(p.username, 0, 40);
	p.len = 140;
	set_username(&p);
	set_msg(&p);
	puts(">: Msg sent!");
}

int main(void)
{
	puts(
		"--------------------------------------------\n" \
		"|   ~Welcome to l33t-m$n ~    v1337        |\n" \
		"--------------------------------------------");

	handle_msg();

	return EXIT_SUCCESS;
}
