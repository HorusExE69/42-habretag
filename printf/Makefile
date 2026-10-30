SRCS = ft_printf.c ft_printf_utils1.c ft_printf_utils2.c
SRCS_BONUS = ft_printf_bonus.c ft_printf_utils1_bonus.c ft_printf_utils2_bonus.c ft_printf_utils3_bonus.c

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
NAME = libftprintf.a
FLAGS = -Wall -Werror -Wextra -g


all: $(NAME)

$(NAME): $(OBJS)
		rm -f $(NAME) .bonus
		ar rcs $(NAME) $^

%.o: %.c ft_printf.h ft_printf_bonus.h
	cc -c $(FLAGS) $< -o $@

bonus : .bonus

.bonus : $(OBJS_BONUS)
		rm -f $(NAME)
		ar rcs $(NAME) $^
		touch .bonus

clean:
		rm -f $(OBJS)
		rm -f $(OBJS_BONUS) .bonus

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re