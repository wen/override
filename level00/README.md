# level00

The program reads a number from stdin, and checks if it's the magic number.

## Step 1. Find the right number

```assembly
level00@OverRide:~$ gdb -batch -ex "set disassembly-flavor intel" -ex "disassemble main" level00
[...]
0x080484de <+74>:	call   0x80483d0 <__isoc99_scanf@plt>
0x080484e3 <+79>:	mov    eax,DWORD PTR [esp+0x1c]
0x080484e7 <+83>:	cmp    eax,0x149c
0x080484ec <+88>:	jne    0x804850d <main+121>
[...]
```
The binary compares the result of function `scanf` with `0x149c`.

```
level00@OverRide:~$ echo 'obase=10; ibase=16; 149C' | bc
5276
```
We converted `0x149c` in decimal `5276`.

## Step 2. Input the number

```
level00@OverRide:~$ ./level00
***********************************
* 	     -Level00 -		  *
***********************************
Password:5276

Authenticated!
$ whoami
level01
$ cat /home/users/$(whoami)/.pass
uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL
```
