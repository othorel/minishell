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
| `Makefile`              | Automates the compilation process for both `fdf` and `fdf_bonus`.                                      |
| `fdf.h`                 | Header file with function prototypes, macros, and necessary includes.                                  |
| `src/*.c`               | Source files containing the logic for graphics rendering, file parsing, and user interactions.         |
| `libft/`                | Custom library for utility functions like `ft_putnbr`, `ft_split`, and others.                        |
| `minilibx-linux/`       | The MiniLibX library for managing graphics and rendering.                                              |
| `obj/`                  | Directory for object files during compilation.                                                        |

---

## 🔧 Compilation Instructions

Use the **Makefile** to compile the project.

### Compile the main program:
```bash
make
```
### Compile the bonus program:
```bash
make bonus
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

Once compiled, you can run the program to display a 3D wireframe of a map.

Run the main program:
```bash
./fdf test_maps/[map].fdf
```

#### Different projections

By pressing `I`, `O` and `P` keys on your keyboard, you will switch projection views to `Isometric`, `Top View` and `Perspective`, respectively. 

<figure>
<figcaption><i>Isometric View</i></figcaption>
<img width="550px" src=https://github.com/othorel/Fil-De-Fer/blob/main/img/Screenshot%20from%202025-01-20%2016-31-01.png alt="FdF Isometric"/>
</figure>
<figure>
<figcaption><i>Top View</i></figcaption>
<img width="550px" src=https://github.com/othorel/Fil-De-Fer/blob/main/img/Screenshot%20from%202025-01-20%2016-34-17.png alt="FdF Top View"/>
</figure>
<figure>
<figcaption><i>Perspective View</i></figcaption>
<img width="550px" src=https://github.com/othorel/Fil-De-Fer/blob/main/img/Screenshot%20from%202025-01-20%2016-32-41.png alt="FdF Perspective"/>
</figure>

---
