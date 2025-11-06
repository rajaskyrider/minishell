# Minishell

Minishell is a lightweight UNIX shell implemented entirely in C. The project is
an exercise in low-level programming: every subsystem from the tokenizer to the
executor is hand-written without the help of high-level frameworks or dynamic
languages. Apart from the POSIX `readline`
interfaces used for interactive input, the shell relies solely on the C
standard library and raw system calls.

## Capabilities
- Interactive prompt with command history, signal-aware behaviour, and status
  reporting.
- Full tokenisation of shell syntax, including quotes, logical operators, and
  parenthesis for subshell execution.
- Parser that builds an Abstract Syntax Tree (AST) to respect operator
  precedence across pipelines (`|`), logical operators (`&&`, `||`), and
  grouped commands.
- Executor that handles external binaries, environment propagation, pipes and
  redirections (`>`, `>>`, `<`, `<<`), and on-the-fly variable expansion.
- Built-in implementations for core shell commands (`cd`, `echo`, `env`,
  `exit`, `export`, `pwd`, `unset`) with in-memory environment management.

## Why It Matters
Building Minishell demonstrates how a traditional shell works from the ground
up:
- Manual memory management, error handling, and resource cleanup keep the code
  close to the operating system.
- Process orchestration uses `fork`, `execve`, `dup2`, and file descriptor
  juggling to stitch pipelines and redirections together.
- Custom data structures (linked lists, AST nodes, environment maps) replace the
  convenience layers you would find in higher-level runtimes.

## Build & Run
```bash
make          # build minishell and bundled libft archive
./minishell   # start the interactive shell
```

### Requirements
- POSIX-compatible system with a C compiler (`cc`/`clang`/`gcc`)
- GNU Readline headers and library (for prompt editing and history)
- Standard development tools: `make`, shell utilities, and pthread support

Run `make clean` to remove object files and `make fclean` to purge the binary
and the `libft` archive.

## Repository Tour
- `main.c`, `prompt.c`, `signals.c`: high-level shell loop, prompt display, and
  signal handling.
- `tokenizer/`: lexical analysis that breaks input into typed tokens.
- `parser/`: AST construction plus input/output bookkeeping.
- `exec/`: command dispatch, piping, redirection, globbing, and variable
  expansion.
- `builtin/`: low-level versions of POSIX built-ins with shared environment
  helpers.
- `libft/`: project-local implementations of common C utilities reused across
  modules.

## Getting More From Minishell
Minishell is designed as a learning playground. Experiment with new features by
extending the tokeniser or AST, add unit tests around the executor, or instrument
the code to trace how commands get transformed as they flow through the shell.
The tight, dependency-free C codebase makes it easy to reason about every step
between a raw command string and the resulting processes.


