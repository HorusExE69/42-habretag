#include "ft_printf_bonus.h"

int	nbr_len_base(unsigned long n, int base)
{
	int	len;

	len = 1;
	while (n >= (unsigned long)base)
	{
		n /= base;
		len++;
	}
	return (len);
}

int	print_nbr_base(unsigned long n, char *base)
{
	unsigned long	blen;
	int				count;

	blen = 0;
	while (base[blen])
		blen++;
	count = 0;
	if (n >= blen)
		count += print_nbr_base(n / blen, base);
	write(1, &base[n % blen], 1);
	return (count + 1);
}

int	print_field(t_fmt *fmt, char *s, int len)
{
	int	count;

	count = 0;
	if (!fmt->minus)
		count += print_padding(' ', fmt->width - len);
	write(1, s, len);
	count += len;
	if (fmt->minus)
		count += print_padding(' ', fmt->width - len);
	return (count);
}

int	print_c(t_fmt *fmt, int c)
{
	char	ch;

	ch = (char)c;
	return (print_field(fmt, &ch, 1));
}

int	print_s(t_fmt *fmt, char *s)
{
	int	len;

	if (!s)
	{
		if (fmt->precision >= 0 && fmt->precision < 6)
			s = "";
		else
			s = "(null)";
	}
	len = 0;
	while (s[len] && (fmt->precision < 0 || len < fmt->precision))
		len++;
	return (print_field(fmt, s, len));
}
