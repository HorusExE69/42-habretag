#include "ft_printf_bonus.h"

void	init_fmt(t_fmt *fmt)
{
	fmt->minus = 0;
	fmt->zero = 0;
	fmt->hash = 0;
	fmt->plus = 0;
	fmt->space = 0;
	fmt->width = 0;
	fmt->precision = -1;
	fmt->conv = '\0';
}

int	print_p(t_fmt *fmt, void *p)
{
	if (!p)
		return (print_field(fmt, "(nil)", 5));
	return (print_number(fmt, (unsigned long)p, "0x", "0123456789abcdef"));
}

int	print_padding(char c, int n)
{
	int	count;

	count = 0;
	while (count < n)
	{
		write(1, &c, 1);
		count++;
	}
	return (count);
}
