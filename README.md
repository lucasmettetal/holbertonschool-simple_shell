# Simple Shell

A simple implementation of a UNIX shell in C, created as part of the Holberton School curriculum.

## Description

This project is a minimal shell inspired by `/bin/sh`. It can execute simple commands with their full paths. The shell reads commands from standard input, parses them, and executes them using the `fork()` and `execve()` system calls.

### Features

- **Command execution**: Execute any program available in the filesystem
- **Interactive & Non-interactive modes**: Works in both interactive mode (with prompt) and piped input
- **Built-in commands**: Basic support for `exit` (work in progress)
- **Environment preservation**: Passes environment variables to executed commands
- **Error handling**: Displays error messages matching the format of `/bin/sh`

## Compilation

```bash
make
```

This will compile the project using `gcc` with the following flags:
- `-Wall -Werror -Wextra -pedantic -std=gnu89`

## Usage

### Interactive Mode

```bash
$ ./hsh
#cisfun$ /bin/ls
[output of ls]
#cisfun$ /bin/cat file.txt
[file contents]
#cisfun$ exit
$
```

### Non-Interactive Mode (Pipe Input)

```bash
$ echo "/bin/ls" | ./hsh
[output of ls]
```

### Examples

```bash
$ ./hsh
#cisfun$ /bin/echo "Hello, World!"
Hello, World!
#cisfun$ /bin/pwd
/path/to/current/directory
#cisfun$ /bin/whoami
username
#cisfun$ exit
```

## Implementation Details

### Architecture

- **main.c**: Entry point and main shell loop
- **prompt.c**: Displays the shell prompt (`#cisfun$`) in interactive mode
- **input.c**: Reads user input line by line using `getline()`
- **Input parsing**: Tokenizes input into command and arguments
- **exec.c**: Handles command execution via `fork()` and `execve()`
- **shell.h**: Header file with all function prototypes and data structures

### Shell State Structure

```c
typedef struct s_shell
{
	char *line;          /* Input line buffer */
	size_t cap;          /* Buffer capacity */
	int status;          /* Last command exit status */
	unsigned long lineno;/* Line number for error reporting */
	int interactive;     /* Interactive mode flag */
	char *prog;          /* Program name (argv[0]) */
	char **env;          /* Environment variables */
} t_shell;

```

## Constraints

- **No global variables**: All state is managed through the `t_shell` structure
- **Standard C89**: Code follows the GNU89 standard
- **Allowed functions**: Limited to a specific set of standard library functions

### Allowed Functions

The following system calls and standard library functions are permitted:

- `access`, `chdir`, `close`, `closedir`, `execve`, `exit`, `_exit`
- `fflush`, `fork`, `free`, `getcwd`, `getline`, `getpid`
- `getppid`, `getuid`, `isatty`, `kill`, `malloc`, `memset`
- `open`, `opendir`, `perror`, `printf`, `fprintf`, `sprintf`
- `putchar`, `puts`, `read`, `readdir`, `signal`, `stat`, `lstat`, `fstat`
- `strtok`, `wait`, `waitpid`, `write`

## File Structure

```
holbertonschool-simple_shell/
├── Makefile           # Build configuration
├── README.md          # This file
├── AUTHORS            # Project authors
├── shell.h            # Header file with prototypes
├── main.c             # Main loop
├── prompt.c           # Prompt display
├── input.c            # Input handling
├── parser.c           # Command parsing
├── exec.c             # Command execution
└── man/               # Manual files
```

## Compilation & Testing

### Compile

```bash
make
```

### Clean Object Files

```bash
make clean
```

### Clean Everything (including executable)

```bash
make fclean
```

### Rebuild

```bash
make re
```

## Error Handling

When a command is not found or cannot be executed, the shell displays an error message in the format:

```
./hsh: 1: command_name: not found
```

Where the number (1 in this example) represents the line number at which the error occurred.

## Authors

Enzo RICHARD
Lucas METTETAL

## Acknowledgments

This project follows the Holberton School simple_shell project specification and Betty coding style guidelines.
