#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LOGFILE "./backups/.log"
#define BACKUPDIR "./backups/"

void log_wrapper(FILE *log_fp, char *info, char *filename)
{
	char buf[255];

	strcpy(buf, info);
	snprintf(buf + strlen(buf), 255 - strlen(buf) - 1, filename);
	buf[strcspn(buf, "\n")] = '\0';
	fprintf(log_fp, "LOG: %s\n", buf);
}

int main(int argc, char *argv[])
{
	char buf[100];

	if (argc != 2)
		printf("Usage: %s filename\n", argv[0]);

	FILE *log_fp = fopen(LOGFILE, "w");
	if (!log_fp) {
		printf("ERROR: Failed to open %s\n", LOGFILE);
		exit(EXIT_FAILURE);
	}

	log_wrapper(log_fp, "Starting back up: ", argv[1]);

	FILE *src_fp = fopen(argv[1], "r");
	if (!src_fp) {
		printf("ERROR: Failed to open %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	strcpy(buf, BACKUPDIR);
	strncat(buf, argv[1], 100 - strlen(buf) - 1);
	int fd = open(buf, O_CREAT | O_EXCL | O_WRONLY, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
	if (fd < 0) {
		printf("ERROR: Failed to open %s%s\n", BACKUPDIR, argv[1]);
		exit(EXIT_FAILURE);
	}

	char c;
	while ((c = fgetc(src_fp)) != EOF)
		write(fd, &c, 1);

	log_wrapper(log_fp, "Finished back up ", argv[1]);

	fclose(src_fp);
	close(fd);

	return EXIT_SUCCESS;
}
