#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/prctl.h>

int main(void)
{
	pid_t pid = fork();
	char buf[128] = {0};
	int syscall = 0;
	int status = 0;

	if (pid == 0) {
		prctl(PR_SET_PDEATHSIG, SIGHUP);
		ptrace(PTRACE_TRACEME, 0, NULL, NULL);
		puts("Give me some shellcode, k");
		gets(buf);
	} else {
		while (1) {
			wait(&status);
			if (WIFEXITED(status) || WIFSIGNALED(status)) {
				puts("child is exiting...");
				break;
			}

			syscall = ptrace(PTRACE_PEEKUSER, child, 4 * ORIG_EAX, NULL);

			if (syscall == 11) {
				puts("no exec() for you");
				kill(child, SIGKILL);
				break;
			}
		}
	}

	return EXIT_SUCCESS;
}
