# minishell

[![42 École](https://img.shields.io/badge/42-École-000000?style=flat&logo=42&logoColor=white)](https://42.fr)

**minishell** is a simple command-line interpreter project developed as part of the 42 École curriculum. It replicates basic shell functionalities, giving students a deep understanding of system programming, process management, and shell scripting concepts.

---

## Table of Contents
- [About the Project](#about-the-project)
- [Features](#features)
- [Getting Started](#getting-started)
- [Installation](#installation)
---

## About the Project

The **minishell** project involves creating a minimalistic Unix shell that can execute commands, handle pipes, and manage the environment. It serves as an introduction to system-level programming, process creation, and inter-process communication.

This project focuses on:
- Parsing and tokenizing command input.
- Managing child processes and system calls.
- Handling signals and interactive user input.

---

## Features

- **Command Execution:** Supports basic shell commands and executable files in the system path.
- **Environment Management:** Replicates behavior of environment variables using `env`, `export`, and `unset`.
- **Pipes:** Implements inter-process communication for piped commands (`ls | grep file`).
- **Redirection:** Supports input and output redirection (`<`, `>`, `>>`).
- **Built-in Commands:** Includes built-ins such as `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.
- **Signal Handling:** Captures and handles signals like `CTRL+C`, `CTRL+Z`, and `CTRL+D`.

---

## Getting Started

### Prerequisites
- A Unix-based operating system (Linux or macOS recommended).
- GCC or another compatible C compiler.
- Make utility.

---

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/hassan-kheireddin/minishell.git
   cd minishell
