_This project has been created as part of the 42 curriculum by alnoukan._

# get_next_line

## Description

`get_next_line` is a C function that returns one line at a time from a file
descriptor:

```c
char	*get_next_line(int fd);
```

Each call returns the next line, including its terminating `\n` (unless it is
the last line of a file that does not end with `\n`). It returns `NULL` once
there is nothing left to read, or if an error occurs. It works on regular
files, standard input and pipes, and reads only as much as it needs to return
the current line.

The goal of the project is to learn how **static variables** keep state
between function calls, and how to manage memory carefully when data arrives
in chunks of arbitrary size.

## Instructions

There is no Makefile: the function is meant to be compiled into another
program. The buffer size used for `read()` is set at compile time:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c your_main.c
```

If `-D BUFFER_SIZE` is omitted, it defaults to 42.

Bonus version (several file descriptors at the same time):

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c your_main.c
```

### Tests

`tests/run_tests.sh` compiles the function with `BUFFER_SIZE` = 0, 1, 2, 3,
42, 9999 and 10000000 and checks, for each one:

- the output is identical to the input file, read from a file, from stdin and
  from a pipe (empty file, no trailing `\n`, only `\n`, a 20 000-character
  line, 20 000 lines, random line lengths);
- the first line is returned without waiting for EOF (the input must not be
  read in full);
- after a read error, the state is cleared and a reopened file starts again
  from the first line;
- an invalid fd returns `NULL`;
- no memory leaks (`leaks` on macOS, `valgrind` on Linux);
- bonus: two files read alternately each come out intact, and fd `-1` or
  `>= MAX_FD` returns `NULL` without crashing.

```sh
sh tests/run_tests.sh
```

## Algorithm

The function keeps one static string, the **stash**, holding bytes that were
read but not yet returned. Each call runs three steps:

1. **`read_to_stash`**: while the stash contains no `\n` and `read()` has not
   reached EOF, read `BUFFER_SIZE` bytes and append them to the stash. It stops
   as soon as a full line is available, so the file is never read further than
   needed.
2. **`extract_line`**: copy the stash up to and including the first `\n` (or
   up to the end if there is none). An empty stash means EOF: return `NULL`.
3. **`trim_stash`**: replace the stash with what comes after that `\n`, freeing
   the old one. If nothing is left, the stash becomes `NULL`, so no memory is
   held once the file is fully read.

**Why this design.** It is the simplest approach that meets the subject's rules:
it reads lazily, so it works on stdin and pipes where the input is not complete
yet, and each step is a small function with a single job. Memory ownership is
explicit: `ft_strjoin_free` always frees the old stash, and every error path
(failed `read()` or `malloc()`) frees the stash and resets it to `NULL`, so the
next call starts clean.

**Bonus.** The only change is that the static variable becomes an array,
`static char *stash[MAX_FD]`, with one stash per file descriptor. Each fd keeps
its own leftover bytes, so reads on different fds never mix. fds outside
`[0, MAX_FD)` are rejected before the array is indexed.

**Cost.** Appending to the stash copies it, so a single line of length _L_ read
with a small `BUFFER_SIZE` costs O(*L*² / `BUFFER_SIZE`) byte copies. That is
fine for normal text, but it is why `BUFFER_SIZE=1` on a very long line is
noticeably slower.

## Resources

- `man 2 read`, `man 3 malloc`
- [Static variables in C](https://en.wikipedia.org/wiki/Static_variable)
- [File descriptors](https://en.wikipedia.org/wiki/File_descriptor)
- 42 Norm (norminette) documentation

### Use of AI

An AI assistant (Claude) was used to review the previous version of this
project, which had several bugs: it read the whole input before returning the
first line, mishandled read errors, and could crash on an invalid fd in the
bonus. It also proposed the restructured version (three helper functions), wrote
the test harness in `tests/`, and drafted this README. All code was reviewed,
tested and understood before submission.
