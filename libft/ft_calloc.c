#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*res;
	size_t	tot;

	if (count == 0 || size == 0)
		return (malloc(0));
	tot = count * size;
	if (tot / count != size)
		return (NULL);
	res = malloc(tot);
	if (!res)
		return (NULL);
	ft_bzero(res, tot);
	return (res);
}
