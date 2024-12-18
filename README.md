# Minishell

## Introduction

Minishell is a project that involves creating a simple shell, similar to bash. This project provides an opportunity to learn about processes, file descriptors, and the inner workings of command-line interfaces.

## Project Overview

The goal is to create a basic shell that can interpret and execute commands, handle environment variables, and implement some built-in functions. This project introduces concepts of process creation, signal handling, and file manipulation.

### Key Features
- Command execution
- Input/output redirection
- Pipes
- Environment variable handling
- Signal handling
- Built-in commands

## Mandatory Part

### Program Name
`minishell`

### Compilation
Compile the program using the provided Makefile with the following rules:
- `make all`: Compile the program
- `make clean`: Remove object files
- `make fclean`: Remove object files and the executable
- `make re`: Recompile the program

### Implementation Requirements

1. Display a prompt for user input
2. Implement a working command history
3. Search and execute the correct executable based on PATH or given path
4. Handle single quotes (') and double quotes (")
5. Implement input/output redirections (<, >, <<, >>)
6. Implement pipes (|)
7. Handle environment variables ($VAR)
8. Handle $? for exit status
9. Handle ctrl-C, ctrl-D, and ctrl-\ signals
10. Implement built-in commands:
   - echo (with -n option)
   - cd (with relative or absolute path)
   - pwd
   - export
   - unset
   - env
   - exit

### Allowed Functions
readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset, sigaddset, kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

## Bonus Part

### Additional Features
- Implement && and || operators with parentheses for priorities
- Implement wildcards (*) for the current working directory

## Guidelines

- The project must be written in C
- Follow the Norm coding style
- No unexpected quits (segmentation fault, bus error, double free, etc.)
- All heap allocated memory must be properly freed
- Handle errors carefully
- No memory leaks

## Evaluation

The mandatory part must be perfect for the bonus part to be evaluated. Ensure all requirements are met and the program functions without any issues.

## Author

aben-hss oussama_rezkellah 

## License

This project is part of the curriculum of 42 School.

