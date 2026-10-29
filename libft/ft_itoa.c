#include "libft.h"

static size_t	count_digit(int n)
{
	size_t	len;
	long	nb;

	len = 1;
	nb = n;
	if (nb < 0)
	{
		len++;
		nb *= -1;
	}
	while (nb > 9)
	{
		nb /= 10;
		len ++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*res;
	long	nb;
	size_t	len;

	nb = n;
	len = count_digit(n);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	if (n == 0)
		res[0] = '0';
	if (nb < 0)
	{
		res[0] = '-';
		nb *= -1;
	}
	res[len] = '\0';
	while (nb > 0)
	{
		res[len - 1] = (nb % 10) + '0';
		nb /= 10;
		len --;
	}
	return (res);
}
