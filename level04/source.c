#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/prctl.h>

int main(void)
{
	pid_t pid = fork();
	char buf[128] = {0};
	int status;

	if (pid == 0) {
		prctl(1, 1);
		ptrace(0, 0, NULL, NULL);
		puts("Give me some shellcode, k");
		gets(buf);
	} else {
		while (1) {
			wait(&status);
			if (status & 0x7f) {
				puts("child is exiting...");
				break;
			}
			if (ptrace(3, pid, 44, NULL) == 11) {
				puts("no exec() for you");
				kill(pid, SIGKILL);
				break;
			}
		}
	}

	return EXIT_SUCCESS;
}
