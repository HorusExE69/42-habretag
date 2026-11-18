/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habretag <habretag@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 11:29:49 by habretag          #+#    #+#             */
/*   Updated: 2026/11/18 11:29:50 by habretag         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	set_flag(char c, t_fmt *fmt)
{
	if (c == '-')
		fmt->minus = 1;
	else if (c == '0')
		fmt->zero = 1;
	else if (c == '#')
		fmt->hash = 1;
	else if (c == '+')
		fmt->plus = 1;
	else if (c == ' ')
		fmt->space = 1;
	else
		return (0);
	return (1);
}

static int	parse_number(const char *str, int *i)
{
	int	n;

	n = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		n = n * 10 + (str[*i] - '0');
		(*i)++;
	}
	return (n);
}

int	parse_format(const char *str, int *i, t_fmt *fmt)
{
	init_fmt(fmt);
	(*i)++;
	while (set_flag(str[*i], fmt))
		(*i)++;
	fmt->width = parse_number(str, i);
	if (str[*i] == '.')
	{
		(*i)++;
		fmt->precision = parse_number(str, i);
	}
	fmt->conv = str[*i];
	return (str[*i] != '\0');
}

static int	tag_print(t_fmt *fmt, va_list *args)
{
	if (fmt->conv == 'c')
		return (print_c(fmt, va_arg(*args, int)));
	else if (fmt->conv == 's')
		return (print_s(fmt, va_arg(*args, char *)));
	else if (fmt->conv == 'p')
		return (print_p(fmt, va_arg(*args, void *)));
	else if (fmt->conv == 'd' || fmt->conv == 'i')
		return (print_int(fmt, va_arg(*args, int)));
	else if (fmt->conv == 'u' || fmt->conv == 'x' || fmt->conv == 'X')
		return (print_unsigned(fmt, va_arg(*args, unsigned int)));
	else if (fmt->conv == '%')
		return (write(1, "%", 1));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	t_fmt	fmt;
	int		i;
	int		tot;

	if (!str)
		return (-1);
	va_start(args, str);
	i = 0;
	tot = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (!parse_format(str, &i, &fmt))
				break ;
			tot += tag_print(&fmt, &args);
		}
		else
			tot += write(1, &str[i], 1);
		i++;
	}
	va_end(args);
	return (tot);
}
