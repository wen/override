# level03

```
(0x1337d00d - INPUT) XOR "Q}|u`sfg~sf{}|a3" = "Congratulations!"
```
According to the disassembly, we knew our input need to be satisfied to the formula above. We XOR these two strings first to get the key by using an [online XOR cipher](https://www.dcode.fr/xor-cipher). `0x12` is the key of XOR. Then the final password is `0x1337d00d - 0x12 = 0x1337CFFB (322424827)`.

```
level03@OverRide:~$ ./level03
***********************************
*		level03		**
***********************************
Password:322424827
$ whoami
level04
$ cat /home/users/$(whoami)/.pass
kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf
```
