# Simple Shell Project

# This is an ALX collaborative project between Joseph Alikah and Michael Onyeweke. We were required to write a simple UNIX command interpreter.

Main shell program

### main

```
exit = -1
path = buildpath()

while exit == -1:
    display_prompt()
    get_input(&buffer)
    arg_list = parse(buffer)
    if (is_builtin(arg_list[0])):
	    exit = run_builtin(arglist)
	    continue
    if is_valid_file(arg_list[0]):
	    run_command(arglist)
	    continue
    if correct_path(arg_list[0]):
	    add_path(arglist)
	    run_command(arglist)
	    continue
    error("No such file or directory")
```

### display_prompt

### run_command

## string.c

Helper string functions

### _strcmp

### concatenate

### _strlen

## environment.c

Functions to help manage the environment

### setenv

### getenv

### delenv

## path.c

Functions to help manage the path.
List of paths is implemented as a linked list.

### buildpath

### add_path

### correct_path

Create a linked list of paths

## built-ins.c

Shell built-ins

### is_builtin

### run_builtin

## arguments.c

Handle arguments

### parse

## io.c

### getline

### print
