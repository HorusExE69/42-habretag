*This project has been created as part of the 42 curriculum by habretag.*

# Libft

## Description

Libft is a static C library created as a reusable toolkit for the 42 curriculum.
It reimplements selected standard C library functions and provides additional
helpers for manipulating strings, memory, and integers, as well as writing to
file descriptors.

Here are the 3 parts of the library :
- **Libc functions:** `ft_isalpha.c`, `ft_isdigit.c`, `ft_isalnum.c`,
  `ft_isascii.c`, `ft_isprint.c`, `ft_strlen.c`, `ft_memset.c`, `ft_bzero.c`,
  `ft_memcpy.c`, `ft_memmove.c`, `ft_strlcpy.c`, `ft_strlcat.c`,
  `ft_toupper.c`, `ft_tolower.c`, `ft_strchr.c`, `ft_strrchr.c`,
  `ft_strncmp.c`, `ft_memchr.c`, `ft_memcmp.c`, `ft_strnstr.c`, `ft_atoi.c`,
  `ft_calloc.c`, `ft_strdup.c`.
- **Additional functions:** `ft_substr.c`, `ft_strjoin.c`, `ft_strtrim.c`,
  `ft_split.c`, `ft_itoa.c`, `ft_strmapi.c`, `ft_striteri.c`,
  `ft_putchar_fd.c`, `ft_putstr_fd.c`, `ft_putendl_fd.c`, `ft_putnbr_fd.c`.
- **Linked lists:** `ft_lstnew.c`, `ft_lstadd_front.c`, `ft_lstsize.c`,
  `ft_lstlast.c`, `ft_lstadd_back.c`, `ft_lstdelone.c`, `ft_lstclear.c`,
  `ft_lstiter.c`, `ft_lstmap.c`.

## Instructions

Use `make` to build the library.
Use `make clean` to remove object files.
Use `make fclean` to remove object files and the library. 
Use `make re` to rebuild.
The project is compiled with `cc -Wall -Wextra -Werror -g`.

## Resources

- The 42 Libft project subject.
- The system manual pages for C functions.

AI was just use to help me for this README (only for the syntaxe of .md)