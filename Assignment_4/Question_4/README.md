# `Question 4`

- Find the required password from the application `program2.exe` for successfull authentication.
- Devise a patch so that the application will accept any password and store it as `program2-patched.exe`. 
- Create a script/patch or application that allows you to replace password with any password, and store it as `program2-password-changer.py`

## Setup
- __Mac OSX, Linux Users__: You'll need to install [Wine](https://www.winehq.org/) in order to run the Windows binaries 
- __Windows Users__: Download & Install [oclHashcat](http://hashcat.net/oclhashcat/).

## Running

```bash
> cd path/to/program2.exe/and/program2-patched.exe
# Password-protected
> program2.exe
# Patched-file
> program2-patched.exe
# Change password for program2.exe by replacing PASSWORD with a password of your choice
> python program2-password-changer.py --password=PASSWORD
```

Default password for `program2.exe` can be found in `result.txt`

Diff between `program2.exe` and `program2-patched.exe` can be found in `program2-patched.diff`.
