# 🌐 Minishell - 42 Project

<p align="center">
  <img src="https://github.com/othorel/minishell/blob/main/img/minishell.png" />
</p>

Welcome to **Minishell**, a project at 42 that explores system programming and shell implementation. In this project, you will build a minimal Unix shell that can execute commands, handle input and output redirection, manage built-in commands, and implement job control features like foreground and background processes.
This project focuses on process management, file I/O redirection, signal handling, and memory management.

---

## 📋 Project Overview

| **Category**            | **Functions**                                                                                           |
|-------------------------|--------------------------------------------------------------------------------------------------------|
| **Mandatory Program**   | `minishell` - Implement the minimal shell capable of executing user commands, handling input/output redirection, and managing built-in commands.|
**Utility functions**   | `malloc` `free` `execve` `fork` `waitpid` `signal` `dup2`, etc...|

---

## 🚀 Key Features

1. **Command Parsing** :
   - The shell should accept user input, split it into commands, and execute them sequentially.
   - It should support basic shell features like piping (`|`), input redirection (`<`), and output redirection (`>`).
   
2. **Built-in Commands** :
   - Implement basic shell built-in commands such as `cd`, `echo`, `exit`, `export`, `unset`, `env`, `pwd`.
   - Handle errors for invalid or incorrect commands.

3. **Process Management** :
   - Use `fork()` to create new processes for each command.
   - Use `execve()` to execute commands within those processes.
   - Handle child process status with `waitpid()`.

4. **Signal Handling** :
   - Properly handle signals like `SIGINT` and `SIGQUIT` to allow for normal terminal control (e.g., pressing `Ctrl+C`).
   - Make sure the shell does not crash on receiving signals.
  
5. **Job control** :
   - Implement foreground and background process management using the `&` operator.
   - Track running processes and allow the user to manage them.

6. **Memory Management** :
   - Ensure proper memory management by freeing allocated memory.
   - Avoid memory leaks and handle errors properly during allocation.

---

## 🗂️ File Structure

| **File**                | **Description**                                                                                        |
|-------------------------|--------------------------------------------------------------------------------------------------------|
| `Makefile`              | Automates the compilation process. Run make to generate the `minishell` executable.                    |
| `minishell.h`           | Header file with function prototypes and necessary includes for the shell program.                     |
| `minishell.c`           | Main program that runs the shell loop and processes user input.                                        |
| `libft/`                | Custom library for utility functions like `ft_putnbr`, `ft_split`, and others.                         |
| `utils.c`               | Utility functions like memory management, command parsing, error handling, etc.                        |
| `builtin.c`             | Implementation of built-in commands such as `cd`, `echo`, `exit`...                                    |
| `execute.c`             | Logic for forking processes and executing commands with `execve()`.                                    |
| `signals.c`             | Signal handling logic, particularly for handling `SIGINT` and `SIGQUIT`.                               |

---

## 🔧 Compilation Instructions

Use the **Makefile** to compile the project.

### Compile the main program:
```bash
make
```
### Clean the project (remove object files):
```bash
make clean
```
### Full cleanup (remove all generated files):
```bash
make fclean
```
### Recompile after cleaning:
```bash
make re
```
---
## 💻 Usage

Once compiled, you can use the `minishell` program as follows:

Run the shell:
```bash
./minishell
```
This will launch the shell, and you can begin typing commands directly.
```bash
$ echo Hello, world!
Hello, world!
$ cd /path/to/directory
$ ls -l
$ exit
```
---
## 🧪 Testing

You can test the functionality of your shell by running various commands, including built-in commands and external commands.

For example:
```bash
$ ./minishell
> echo Hello, world!
Hello, world!
> cd /nonexistent/path
cd: no such file or directory: /nonexistent/path
> ls -l
> exit
```
---
## 🤝 Contributing

If you'd like to contribute to this project, feel free to fork the repository, make your changes, and submit a pull request!

---


