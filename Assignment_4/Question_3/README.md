# `Question 3`

Find the required password from the application `program1.exe` for successfull authentication. Also devise a patch so that the application will accept any password and store it as `program1-patched.exe`. 

## Setup
If you're running the programs on Mac OSX or Linux, you'll need to install [Wine](https://www.winehq.org/). Windows users do not need to setup anything.

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
