/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils3_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habretag <habretag@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 11:30:02 by habretag          #+#    #+#             */
/*   Updated: 2026/11/18 11:30:03 by habretag         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	str_len(char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

static int	calc_zeros(t_fmt *fmt, int digits, int plen)
{
	int	zeros;

	zeros = 0;
	if (fmt->precision > digits)
		zeros = fmt->precision - digits;
	if (fmt->zero && !fmt->minus && fmt->precision < 0)
		zeros = fmt->width - plen - digits;
	if (zeros < 0)
		zeros = 0;
	return (zeros);
}

int	print_number(t_fmt *fmt, unsigned long n, char *prefix, char *base)
{
	int	digits;
	int	zeros;
	int	plen;
	int	pad;

	digits = nbr_len_base(n, str_len(base));
	if (fmt->precision == 0 && n == 0)
		digits = 0;
	plen = str_len(prefix);
	zeros = calc_zeros(fmt, digits, plen);
	pad = fmt->width - plen - zeros - digits;
	if (pad < 0)
		pad = 0;
	if (!fmt->minus)
		print_padding(' ', pad);
	write(1, prefix, plen);
	print_padding('0', zeros);
	if (digits)
		print_nbr_base(n, base);
	if (fmt->minus)
		print_padding(' ', pad);
	return (pad + plen + zeros + digits);
}

int	print_int(t_fmt *fmt, int n)
{
	long	nb;
	char	*prefix;

	nb = n;
	prefix = "";
	if (nb < 0)
	{
		prefix = "-";
		nb = -nb;
	}
	else if (fmt->plus)
		prefix = "+";
	else if (fmt->space)
		prefix = " ";
	return (print_number(fmt, (unsigned long)nb, prefix, "0123456789"));
}

int	print_unsigned(t_fmt *fmt, unsigned long n)
{
	char	*prefix;

	if (fmt->conv == 'u')
		return (print_number(fmt, n, "", "0123456789"));
	prefix = "";
	if (fmt->hash && n != 0 && fmt->conv == 'X')
		prefix = "0X";
	else if (fmt->hash && n != 0)
		prefix = "0x";
	if (fmt->conv == 'X')
		return (print_number(fmt, n, prefix, "0123456789ABCDEF"));
	return (print_number(fmt, n, prefix, "0123456789abcdef"));
}
