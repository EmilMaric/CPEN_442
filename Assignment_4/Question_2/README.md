# `Question 2`

The following is a hashed password. Passwords are 6 characters long and include any character from the following set `abcdefghijklmnopqarstuvqxyzABCDEFGHIJKLMNOPQRSTUVWXWZ1234567890!@#$%^&*()_+-=`. Find the password given the following hash.

Hashed Password: `CS0DF2939D499DCC46A693653DB281FDBB016B502B`

**Not given in problem, but note that first two characters are the salt that is stored along with the hashed password*

## Setup

Download & Install [oclHashcat](http://hashcat.net/oclhashcat/).

## Running

I've only tested this on Windows with oclHashcat.

```bash
> cd path/to/oclHashcat
# For 32-bit machines, replace cudaHashcat64.exe with cudaHashcat32.exe
> cudaHashcat64.exe -a 3 -m 110 path/to/pwd2.txt ?d?d?d?d
```
