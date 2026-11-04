*This project has been created as part of the 42 curriculum by habretag.*

# ft_printf

## Description

ft_printf is a static library (`libftprintf.a`) that recodes the `printf()`
function of the C standard library. It writes on the standard output and
returns the number of characters printed, like the original.

Supported conversions: `%c`, `%s`, `%p`, `%d`, `%i`, `%u`, `%x`, `%X`, `%%`.

The bonus part also handles the flags `-`, `0`, `.` (precision), `#`, `+`,
` ` (space) and the minimum field width, in any combination.

## Instructions

```sh
make          # builds libftprintf.a (mandatory part)
make bonus    # builds libftprintf.a with the bonus part
make clean    # removes object files
make fclean   # removes object files and the library
make re       # rebuilds everything
```

Use it in a program:

```c
#include "ft_printf.h"

int	main(void)
{
	ft_printf("%s has %d%%\n", "battery", 42);
	return (0);
}
```

```sh
cc -Wall -Wextra -Werror main.c libftprintf.a
```

## Algorithm and data structure

**Mandatory part.** `ft_printf` walks through the format string once. Normal
characters are written directly. When it meets a `%`, it reads the next
character and calls `tag_print`, which takes the next argument from the
`va_list` with the right type (`int`, `char *`, `void *`, `unsigned int`)
and sends it to a small printing function (`ft_print_char`, `ft_print_str`,
`ft_print_nbr`, `ft_print_unsigned`, `ft_print_hex`, `ft_print_ptr`).

- Every printing function returns the number of characters it wrote, so the
  total is the sum of the return values.
- Numbers are printed recursively: the function prints `n / base` first,
  then the last digit `n % base`, which puts the digits in the right order.
- One function, `ft_print_hex`, handles `%x`, `%X` and `%p`: it takes an
  `unsigned long` (large enough for a 64-bit address) and a flag choosing
  lowercase or uppercase digits.
- The `va_list` is passed by address (`va_list *`) to `tag_print`, so the
  position in the arguments is kept between calls on every system.
- Nothing is buffered and nothing is allocated: each part is written with
  `write` as soon as it is known, as the subject requires.

**Bonus part.** A format like `%-08.3d` is first parsed into a structure:

```c
typedef struct s_fmt
{
	int		minus;
	int		zero;
	int		hash;
	int		plus;
	int		space;
	int		width;
	int		precision;	/* -1 when absent */
	char	conv;
}	t_fmt;
```

The structure keeps all the options of one conversion in one place, which is
easier to pass around than many separate variables and respects the Norm
limits on parameters and variables.

Then, for numbers, every length is computed **before** writing anything:
number of digits, prefix (`-`, `+`, ` `, `0x`), zeros required by the
precision or by the `0` flag, and padding spaces. The output is always
written in the same order:

```
[spaces if no '-'] [prefix] [zeros] [digits] [spaces if '-']
```

This order explains the behaviours of printf, for example `%05d` with `-42`
gives `-0042` (the sign is a prefix, written before the zeros), and the `0`
flag is ignored when `-` or a precision is present.

## Resources

- `man 3 printf` and `man 3 stdarg`
- The C standard description of `printf` (ISO C, section 7.21.6.1)

AI (Claude) was used to explain variadic functions and bonus. I also use it for this readme.
