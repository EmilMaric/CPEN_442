# `Question 1`

The following is a hashed password. The password is similar to what is used for debit and credit cards or for locking phones, and it is a 4-digit password. Find the password given the following hash.

Hashed Password: `LTF6A2CBE86F0354722C9B377E9E187885D1DE6B5D`

**Not given in problem, but note that first two characters are the salt that is stored along with the hashed password*

## Setup

Download & Install [oclHashcat](http://hashcat.net/oclhashcat/).

## Running

I've only tested this on Windows with oclHashcat.

```bash
> cd path/to/oclHashcat
# For 32-bit machines, replace cudaHashcat64.exe with cudaHashcat32.exe
> cudaHashcat64.exe -a 3 -m 110 path/to/pwd1.txt ?d?d?d?d
```

Results are stored in `result.txt`.
