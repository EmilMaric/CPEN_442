# `Question 2`

The following is a hashed password. Passwords are 6 characters long and include any character from the given char-set. Find the password given the following hash.

__Hashed Password__: `CS0DF2939D499DCC46A693653DB281FDBB016B502B`</br>
__Char-set__: `abcdefghijklmnopqarstuvqxyzABCDEFGHIJKLMNOPQRSTUVWXWZ1234567890!@#$%^&*()_+-=`

**Not given in problem, but note that first two characters of the hashed password are the salt and are stored along with the hashed password*

## Setup

Download & Install [oclHashcat](http://hashcat.net/oclhashcat/).

## Running

I've only tested this on Windows with oclHashcat.

```bash
> cd path/to/oclHashcat
# For 32-bit machines, replace cudaHashcat64.exe with cudaHashcat32.exe
> cudaHashcat64.exe -a 3 -m 120 -1 ?l?u?d!@#$%^&*()_+-= path/to/pwd2.txt ?1?1?1?1?1?1
```

Results are stored in `result.txt`.
