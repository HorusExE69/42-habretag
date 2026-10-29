#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	b;
	int	c;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
	}
	else
	{
		if (n < 0)
		{
			ft_putchar_fd('-', fd);
			n = -n;
		}
		b = n / 10;
		c = n % 10;
		if (b != 0)
		{
			ft_putnbr_fd(b, fd);
		}
		ft_putchar_fd(c + '0', fd);
	}
}
