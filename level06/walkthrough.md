# level06

The program reads a username and a serial number from stdin. It uses an unknown algorithm to calculate a hash based on username then compares the hash with user's input serial number. Besides that, the binary calls `ptrace` to prevent us from using GDB.

## Step 1. Set GDB breakpoint
```
level06@OverRide:~$ gdb -batch -ex "set disassembly-flavor intel" -ex "disassemble auth" level06
[...]
   0x080487b5 <+109>:	call   0x80485f0 <ptrace@plt>
   0x080487ba <+114>:	cmp    eax,0xffffffff
=> 0x080487bd <+117>:	jne    0x80487ed <auth+165>
[...]
   0x08048863 <+283>:	mov    eax,DWORD PTR [ebp+0xc]
   0x08048866 <+286>:	cmp    eax,DWORD PTR [ebp-0x10]
=> 0x08048869 <+289>:	je     0x8048872 <auth+298>
   0x0804886b <+291>:	mov    eax,0x1
   0x08048870 <+296>:	jmp    0x8048877 <auth+303>
   0x08048872 <+298>:	mov    eax,0x0
[...]

Breakpoint 1: 0x080487bd => Jump to 0x080487ed
Breakpoint 2: 0x08048869 => Show value in stack to get hash
```
After calling `ptrace`, the program compares the return value of `ptrace` with `-1`, so we set first breakpoint `0x080487bd` before jump-not-equal instruction then jump to `0x80487ed`. Next, we set breakpoint `0x08048869` after the whole magic calculation procedure and before jump-equal instruction.

## Step 2. Run the program in GDB
```
level06@OverRide:~$ gdb -q level06
Reading symbols from /home/users/level06/level06...(no debugging symbols found)...done.
(gdb) break *0x080487bd
Breakpoint 1 at 0x80487bd
(gdb) break *0x08048869
Breakpoint 2 at 0x8048869
(gdb) run
Starting program: /home/users/level06/level06
***********************************
*		level06		  *
***********************************
-> Enter Login: admin2
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 42

Breakpoint 1, 0x080487bd in auth ()
(gdb) jump *0x080487ed
Continuing at 0x80487ed.

Breakpoint 2, 0x08048869 in auth ()
(gdb) info registers eax
eax            0x2a	42
(gdb) x/d $ebp-0x10
0xffffd698:	6230696
```
We run the program input a username whose length must be greater than 5, then the program reach the first breakpoint. We skip all the ptrace block by jumping then hit the second breakpoint, now we have our magic hash `6230696` for username `admin2`.

## Step 3. Input correct serial number to get shell
```
level06@OverRide:~$ ./level06
***********************************
*		level06		  *
***********************************
-> Enter Login: admin2
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 6230696
Authenticated!
$ whoami
level07
$ cat /home/users/$(whoami)/.pass
GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8
```
