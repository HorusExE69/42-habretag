/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habretag <habretag@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 11:29:42 by habretag          #+#    #+#             */
/*   Updated: 2026/11/18 11:29:43 by habretag         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H
# include <unistd.h>
# include <stdarg.h>

typedef struct s_fmt
{
	int		minus;
	int		zero;
	int		hash;
	int		plus;
	int		space;
	int		width;
	int		precision;
	char	conv;
}	t_fmt;

int		parse_format(const char *str, int *i, t_fmt *fmt);
int		print_padding(char c, int n);
int		nbr_len_base(unsigned long n, int base);
int		print_nbr_base(unsigned long n, char *base);
int		print_field(t_fmt *fmt, char *s, int len);
int		print_c(t_fmt *fmt, int c);
int		print_s(t_fmt *fmt, char *s);
int		print_int(t_fmt *fmt, int n);
int		print_unsigned(t_fmt *fmt, unsigned long n);
int		print_p(t_fmt *fmt, void *p);
int		print_number(t_fmt *fmt, unsigned long n, char *prefix, char *base);
void	init_fmt(t_fmt *fmt);
int		ft_printf(const char *str, ...);

#endif
