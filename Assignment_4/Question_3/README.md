# `Question 3`

- Find the required password from the application `program1.exe` for successfull authentication. 
- Devise a patch so that the application will accept any password and store it as `program1-patched.exe`. 

## Setup
- __Mac OSX, Linux Users__: You'll need to install [Wine](https://www.winehq.org/) in order to run the Windows binaries 
- __Windows Users__: Do not need to setup anything

## Running

```bash
> cd path/to/program1.exe/and/program1-patched.exe
# Password-protected
> program1.exe
# Patched-file
> program1-patched.exe
```

Password for `program1.exe` can be found in `result.txt`

Diff between `program1.exe` and `program-patched.exe` can be found in `program-patched.diff`.
