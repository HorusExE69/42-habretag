*This project has been created as part of the 42 curriculum by habretag.*

# get_next_line

## Description

`get_next_line(int fd)` returns the next line read from a file descriptor,
including the final `\n` (except for a last line without `\n`). Calling it in
a loop reads a file, or the standard input, one line at a time. It returns
`NULL` when there is nothing left to read or when an error occurs.

The bonus version reads from several file descriptors at the same time
without mixing them, using a single static variable.

## Instructions

There is no Makefile: the function is compiled with the program that uses it.
`BUFFER_SIZE` sets how many bytes are read at a time (42 by default).

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line_bonus.c get_next_line_utils_bonus.c
```

```c
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}
```

## Algorithm

`read()` reads a fixed number of bytes (`BUFFER_SIZE`), not a line. A read
can stop in the middle of a line, or contain the end of one line and the
beginning of the next. The bytes already read after the `\n` cannot be given
back to the file (`lseek` is forbidden), so they are kept in a **static
variable**, the `stash`, which keeps its value between two calls.

Each call works in three steps:

1. **Fill the stash** (`read_to_stash`): while the stash contains no `\n`,
   read `BUFFER_SIZE` bytes and append them to the stash. Stop at the first
   `\n` or at the end of the file. If the stash already contains a `\n` from
   the previous call, nothing is read at all.
2. **Extract the line** (`stash_to_line`): copy the stash up to and
   including the first `\n` (or up to the end if there is none).
3. **Keep the rest** (`stash_to_rest`): copy what comes after the line into a
   new string, free the old stash and keep the rest for the next call.

Example with `"abc\ndef"` and `BUFFER_SIZE=3`:

```
call 1: read "abc", read "\nde"  -> returns "abc\n", stash = "de"
call 2: read "f", read -> 0      -> returns "def",   stash = NULL
call 3: read -> 0, stash empty   -> returns NULL
```

**Why this approach:**

- It reads only what is needed for the current line, as the subject asks,
  instead of reading the whole file first.
- It works for any `BUFFER_SIZE`, from 1 to very large values: the buffer is
  allocated with `malloc` (a 10 MB array on the stack would overflow it).
- The stash is set back to `NULL` and freed at the end of the file and on
  every error (`read` returning -1, failed `malloc`), so there are no leaks
  and no old data is returned later.

**Bonus:** the static variable becomes an array of stashes,
`static char *stash[FD_MAX]`, indexed by the file descriptor. Each fd keeps
its own stash, so calls on fd 3, 4, 5, 3, 4... never mix their lines. The
helper functions are unchanged: only `get_next_line` chooses which stash to
use. File descriptors outside `0..FD_MAX - 1` return `NULL`.

## Resources

- `man 2 read`
- Documentation on static variables in C (storage duration)

AI (Claude) was used to explain static variables and the reading algorithm,
to review the code and point out bugs, to help split the function and write
the bonus part, and to write the test programs. All the code was read,
tested and understood before being submitted.
