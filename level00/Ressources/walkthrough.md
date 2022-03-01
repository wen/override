# level00

```assembly
80484de:	e8 ed fe ff ff       	call   80483d0 <__isoc99_scanf@plt>
80484e3:	8b 44 24 1c          	mov    eax,DWORD PTR [esp+0x1c]
80484e7:	3d 9c 14 00 00       	cmp    eax,0x149c
```
The binary `level00` compares the result of function `scanf` to `0x149c`.

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
Login with password `5276`.
