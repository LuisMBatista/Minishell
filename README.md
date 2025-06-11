# 🐚 Minishell

A simplified Unix shell, developed as part of the 42 School curriculum.  
This project was built collaboratively with [@tiagorsss](https://github.com/tiagorsss) 

---

## 📌 Project Description

The goal of **Minishell** is to recreate a minimal version of a shell—like `bash`—with its own parser and execution environment. It mimics the behavior of a real shell while providing a deep dive into process management, memory handling, and system calls in UNIX.

This project was developed in C, following the strict coding standards of 42.

---

## ⚙️ Features

- Interactive prompt
- Line editing with `readline`
- Support for:
  - **Pipes** (`|`)
  - **Redirections** (`>`, `>>`, `<`, `<<`)
  - **Built-in commands** (`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`)
  - **Environment variable expansion** (`$VAR`)
  - **Quotes** (`'`, `"`)
  - **Signal handling** (`Ctrl+C`, `Ctrl+\`)
  - **Exit status** management
- No memory leaks (checked with `valgrind`)

---

## 🛠️ Built-in Commands

| Command  | Description                |
|----------|----------------------------|
| `echo`   | Print text to stdout       |
| `cd`     | Change directory           |
| `pwd`    | Print working directory    |
| `export` | Set environment variable   |
| `unset`  | Unset environment variable |
| `env`    | Show environment variables |
| `exit`   | Exit the shell             |

---

🚧 Limitations
No support for &&, ||, ;

No advanced job control (fg, bg, etc.)

Not a full Bash replacement

🧠 What We Learned
Process forking and execve

File descriptors and redirections

Lexical analysis and parsing

Signal handling and terminal control

Dynamic memory management in C


## 📦 Installation & Usage

### Prerequisites

- A Unix-like system (Linux or macOS)
- `make` and `gcc`
- `readline` library installed (`brew install readline` or `sudo apt install libreadline-dev`)

### Clone and Run

```bash
git clone https://github.com/yourGitHubUsername/minishell.git
cd minishell
make
./minishell


