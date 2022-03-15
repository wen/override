# level03

The program reads a number from stdin and converts the number to a string by an unknown algorithm. Then it compares the result string with `Congratulations!`.

## Step 1. Solve the equation
```
(0x1337d00d - INPUT) XOR 'Q' = 'C'
```
```
level03@OverRide:~$ perl -e 'printf "%d\n", 0x1337d00d - (ord(C) ^ ord(Q))'
322424827
```
According to the disassembly, we knew our input need to be satisfied to the formula above. We reversed the calculation procedure to get right number.

## Step 2. Input the number
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
