# level06

```
level06@OverRide:~$ gdb -q level06
Reading symbols from /home/users/level06/level06...(no debugging symbols found)...done.
(gdb) break *0x080487ba
Breakpoint 1 at 0x80487ba
(gdb) break *0x08048866
Breakpoint 2 at 0x8048866
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

Breakpoint 1, 0x080487ba in auth ()
(gdb) jump *0x080487ed
Continuing at 0x80487ed.

Breakpoint 2, 0x08048866 in auth ()
(gdb) info registers eax
eax            0x2a	42
(gdb) x/wx $ebp-0x10
0xffffd698:	0x005f12a8
(gdb) p *(unsigned int*)($ebp-0x10)
$1 = 6230696
```

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
